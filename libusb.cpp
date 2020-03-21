#include <iostream>
#include <libusb.h>

using namespace std;

void printdev(libusb_device *dev); //prototype of the function

int main() {
    //pointer to pointer of device, used to retrieve a list of devices
    libusb_device **devs = nullptr;
	libusb_context *ctx = nullptr;
	int r = 0;
    //initialize a library session
	r = libusb_init(&ctx);
	if (r < 0) {
		cout << "Init Error " << r << endl;
		return 1;
	}
    //set verbosity level to 3, as suggested in the documentation
	libusb_set_debug(ctx, 3);
    //get the list of devices
    //holding number of devices in list
	ssize_t cnt = libusb_get_device_list(ctx, &devs);
	if (cnt < 0) {
		cout << "Get Device Error" << endl;
	}
	cout << cnt << " Devices in list." << endl;
	for(ssize_t i = 0; i < cnt; i++) {
		printdev(devs[i]);
	}
	libusb_free_device_list(devs, 1);
	libusb_exit(ctx);
	return 0;
}

void printdev(libusb_device *dev) {
	libusb_device_descriptor desc{};
	int r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0) {
		cout << "failed to get device descriptor" << endl;
		return;
	}
	cout << "Number of possible configurations: " << desc.bNumConfigurations;
	cout << " Device Class: " << desc.bDeviceClass;
	cout << " VendorID: " << desc.idVendor;
	cout << " ProductID: "<< desc.idProduct << endl;
	libusb_config_descriptor *config;
	libusb_get_config_descriptor(dev, 0, &config);
	cout << "Interfaces: " << config->bNumInterfaces << " ||| ";
	const libusb_interface *inter;
	const libusb_interface_descriptor *interdesc;
	const libusb_endpoint_descriptor *epdesc;
	for(int i = 0; i < config->bNumInterfaces; i++) {
		inter = &config->interface[i];
		cout << "Number of alternate settings: " << inter->num_altsetting <<" | ";
		for(int j = 0; j < inter->num_altsetting; j++) {
			interdesc = &inter->altsetting[j];
			cout << "Interface Number: " << interdesc->bInterfaceNumber << " | ";
			cout << "Number of endpoints: " << interdesc->bNumEndpoints << " | ";
			for(int k = 0; k < interdesc->bNumEndpoints; k++) {
				epdesc = &interdesc->endpoint[k];
				cout << "Descriptor Type: " << epdesc->bDescriptorType << " | ";
				cout << "EP Address: " << epdesc->bEndpointAddress << " | ";
			}
		}
	}
	cout << endl << endl << endl;
	libusb_free_config_descriptor(config);
}
