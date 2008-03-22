/*
 * Declaration file for NovInt Falcon User Space Driver - Bootloader and Base Functionality
 *
 * Copyright (c) 2007-2008 Kyle Machulis/Nonpolynomial Labs <kyle@nonpolynomial.com>
 *
 * More info on Nonpolynomial Labs @ http://www.nonpolynomial.com
 *
 * Sourceforge project @ http://www.sourceforge.net/projects/libnifalcon
 *
 * This library is covered by the MIT License, read LICENSE for details.
 */

#ifndef LIBNIFALCON_H
#define LIBNIFALCON_H

#ifdef WIN32
#include <windows.h>
#endif
#ifdef LIBFTDI
#include <ftdi.h>
#else
#include <ftd2xx.h>
#endif

/// Typedef over the FTDI driver handle
#ifdef LIBFTDI
typedef struct ftdi_context* falcon_device;
#else
typedef FT_HANDLE falcon_device;
#endif

/// VID for the Novint Falcon
#define NOVINT_FALCON_VENDOR_ID 0x0403
/// PID for the Novint Falcon
#define NOVINT_FALCON_PRODUCT_ID 0xcb48


int nifalcon_init(falcon_device* dev);

/** 
 * Counts the number of devices connected to the system
 *
 * @param dev Pointer to device (can be null for ftd2xx)
 * 
 * @return Number of falcons connected, -1 on error
 */
int nifalcon_get_count(falcon_device dev);

/** 
 * Opens the device
 * 
 * @param dev Pointer to store opened device handle
 * @param device_index Index of the device to open (for multiple devices)
 * 
 * @return FT_OK on success, FTDI driver error on failure
 */
int nifalcon_open(falcon_device* dev, unsigned int device_index);

/** 
 * Closes device passed to it
 * 
 * @param dev Device handle to close
 *
 * @return FT_OK on success, FTDI driver error on failure
 */
int nifalcon_close(falcon_device dev);

/** 
 * Runs initialization sequence for the device, including loading the firmware onto the internal microcontroller
 *
 * @param dev Device handle to initialize
 * @param firmware_filename Filename of the firmware to load onto the device
 *
 * @return FT_OK on success, FTDI driver error on failure
 */
int nifalcon_load_firmware(falcon_device dev, const char* firmware_filename);

/** 
 * Wrapper for FTDI read functions to do non-blocking, timeout capable read
 *
 * @param dev Device handle to initialize
 * @param str Data to send to device
 * @param size Size of data to send to device
 * @param timeout_ms Send timeout, in milliseconds
 * @param bytes_read Pointer to an int, stores the number of bytes read (in case time out is reached)
 *
 * @return FT_OK on success, FTDI driver error on failure
 */
int nifalcon_read_wait(falcon_device dev, char* str, unsigned int size, unsigned int timeout_ms, unsigned int* bytes_read);

int nifalcon_write(falcon_device dev, char* str, unsigned int size, unsigned int* bytes_written);

#endif