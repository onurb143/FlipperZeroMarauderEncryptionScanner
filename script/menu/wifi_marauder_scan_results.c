#include "wifi_marauder_scan_results.h"
#include <stdio.h> // Tilføj denne linje

void display_scan_results() {
    for(int i = 0; i < num_scanned_devices; i++) {
        ScannedDevice device = scanned_devices[i];
        printf(
            "SSID: %s, RSSI: %d, Encryption: %d\n", device.ssid, device.rssi, device.encryption);
    }
}
