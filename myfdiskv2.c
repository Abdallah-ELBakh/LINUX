#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <aio.h>

#define SECTOR_SIZE 512
#define NUM_PARTITION_ENTRIES 4

typedef struct {
    uint8_t status;
    uint8_t first_chs[3];
    uint8_t partition_type;
    uint8_t last_chs[3];
    uint32_t lba;
    uint32_t sector_count;
} PartitionEntry;
void read_ebrs(const char *disk_device, PartitionEntry extended_partition);
int count_ebrs(const char *disk_device, uint32_t ebr_lba);

void read_partition_table(const char *disk_device) {
    int fd = open(disk_device, O_RDONLY);
    if (fd == -1) {
        perror("Error opening disk device");
        return;
    }

    char mbr[SECTOR_SIZE];
    if (read(fd, mbr, SECTOR_SIZE) != SECTOR_SIZE) {
        perror("Error reading MBR");
        close(fd);
        return;
    }
    close(fd);

    PartitionEntry *partition_table = (PartitionEntry *)&mbr[0x1BE];
    for (int i = 0; i < NUM_PARTITION_ENTRIES; i++) {
        printf("Partition %d:\n", i + 1);
        printf("Status: 0x%02X\n", partition_table[i].status);
        printf("Partition Type: 0x%02X\n", partition_table[i].partition_type);
        printf("First LBA: %" PRIu32 "\n", partition_table[i].lba);
        printf("Sector Count: %" PRIu32 "\n", partition_table[i].sector_count);

        if (partition_table[i].partition_type == 0x05 || partition_table[i].partition_type == 0x0F) {
            printf("Extended partition found. Reading EBRs...\n");
            read_ebrs(disk_device, partition_table[i]);
        }
    }
}
void read_ebrs(const char *disk_device, PartitionEntry extended_partition) {
    int fd = open(disk_device, O_RDONLY);
    if (fd == -1) {
        perror("Error opening disk device");
        return;
    }

    char ebr[512];
    printf("LBA before offset : %u\n",extended_partition.lba);
    off_t ebr_offset = (off_t)(extended_partition.lba) *512;
    printf("EBR offset: %" PRId64 "\n", ebr_offset); // Debug print
    if (pread(fd, ebr, sizeof(ebr), ebr_offset) != SECTOR_SIZE) {
        perror("Error reading EBR");
        close(fd);
        return;
    }
    

    PartitionEntry *logical_partitions = (PartitionEntry *)&ebr[0x1BE];
    int count = 0;
    uint32_t partition_stat=0;
    if(logical_partitions[count].lba != 0)
    {
    	partition_stat=logical_partitions[count].lba;
	count++;
    }
    while(partition_stat !=0)
    {
	    partition_stat = logical_partitions[count].lba;
	if(partition_stat!=0)
   	{
        	count++;
	}
    }
    printf("LB count : %u\n",count);
    for (int i = 0; i < NUM_PARTITION_ENTRIES; i++) {
        printf("  Logical Partition %d:\n", i + 5);
        printf("  Status: 0x%02X\n", logical_partitions[i].status);
        printf("  Partition Type: 0x%02X\n", logical_partitions[i].partition_type);
        printf("  First LBA: %" PRIu32 "\n", logical_partitions[i].lba);
        printf("  Sector Count: %" PRIu32 "\n", logical_partitions[i].sector_count);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <disk_device>\n", argv[0]);
        return 1;
    }

    read_partition_table(argv[1]);

    return 0;
}
