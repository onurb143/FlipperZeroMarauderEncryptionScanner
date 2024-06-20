#ifndef WIFI_MARAUDER_SCAN_RESULTS_H
#define WIFI_MARAUDER_SCAN_RESULTS_H

typedef struct {
    char ssid[32];
    int rssi;
    int encryption;
} ScannedDevice;

extern int num_scanned_devices;
extern ScannedDevice* scanned_devices;

#endif // WIFI_MARAUDER_SCAN_RESULTS_H
