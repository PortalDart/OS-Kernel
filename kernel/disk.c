#include <stddef.h>
#include "io.h"
#include <stdint.h>
#include "kernel.h"

#define WORD_COUNT 256

// -------------------------
// I/O Ports (Primary IDE)
// -------------------------
#define IDE_DATA        0x1F0  // Data register (read/write sector data)
#define IDE_ERROR       0x1F1  // Error register (read error codes)
#define IDE_FEATURES    0x1F1  // Features register (set features for write)
#define IDE_SECTOR_CNT  0x1F2  // Sector count (number of sectors to read/write)
#define IDE_LBA_LOW     0x1F3  // LBA bits 0-7
#define IDE_LBA_MID     0x1F4  // LBA bits 8-15
#define IDE_LBA_HIGH    0x1F5  // LBA bits 16-23
#define IDE_DRIVE_HEAD  0x1F6  // Drive select + LBA bits 24-27
#define IDE_STATUS      0x1F7  // Status register (read) / Command register (write)

// -------------------------
// Status Register Bits
// -------------------------
#define IDE_STATUS_BSY  0x80  // Busy (1 = disk is busy)
#define IDE_STATUS_DRDY 0x40  // Drive ready
#define IDE_STATUS_DF   0x20  // Device fault
#define IDE_STATUS_DSC  0x10  // Drive seek complete
#define IDE_STATUS_DRQ  0x08  // Data request ready (disk ready for read/write)
#define IDE_STATUS_CORR 0x04  // Corrected data (ECC)
#define IDE_STATUS_IDX  0x02  // Index (obsolete)
#define IDE_STATUS_ERR  0x01  // Error

// -------------------------
// Commands
// -------------------------
#define IDE_CMD_READ_SECTORS  0x20  // Read sectors
#define IDE_CMD_WRITE_SECTORS 0x30  // Write sectors
#define IDE_CMD_IDENTIFY      0xEC  // Identify device

// -------------------------
// Drive Selection
// -------------------------
#define IDE_DRIVE_MASTER 0xE0  // Select master drive
#define IDE_DRIVE_SLAVE  0xF0  // Select slave drive


void wait_disk() {
    while (inb(IDE_STATUS) & IDE_STATUS_BSY);
    while (!(inb(IDE_STATUS) & IDE_STATUS_DRQ));
}

void write_disk(uint32_t lba, uint8_t *buffer) {
    outb(IDE_SECTOR_CNT, 1);
    outb(IDE_LBA_LOW, (uint8_t)(lba & 0xFF));
    outb(IDE_LBA_MID, (uint8_t)(lba >> 8));
    outb(IDE_LBA_HIGH, (uint8_t)(lba >> 16));
    outb(IDE_DRIVE_HEAD, IDE_DRIVE_MASTER | ((lba >> 24) & 0x0F));

    outb(IDE_STATUS, IDE_CMD_WRITE_SECTORS);

    wait_disk();

    for (size_t i = 0; i < WORD_COUNT; i++) {
        outw(IDE_DATA, ((uint16_t *)buffer)[i]);
    }

}

void read_disk(uint32_t lba, uint8_t *buffer) {
    outb(IDE_SECTOR_CNT, 1);
    outb(IDE_LBA_LOW, (uint8_t)(lba & 0xFF));
    outb(IDE_LBA_MID, (uint8_t)(lba >> 8));
    outb(IDE_LBA_HIGH, (uint8_t)(lba >> 16));
    outb(IDE_DRIVE_HEAD, IDE_DRIVE_MASTER | ((lba >> 24) & 0x0F));
    outb(IDE_STATUS, IDE_CMD_READ_SECTORS);

    wait_disk();

    for (size_t i = 0; i < WORD_COUNT; i++) {
        ((uint16_t *)buffer)[i] = inw(IDE_DATA);
    }

}
