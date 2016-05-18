#pragma once

#include <linux/spi/spi.h>

struct spi_device* psoc4_get_device(void);
int psoc4_spi_read(struct spi_device *spi, u16* rxData);
int psoc4_spi_write(struct spi_device *spi, u16 txDate);
int psoc4_spi_init(void);
void psoc4_spi_exit(void);