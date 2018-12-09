#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main() {
	int rc;
	char location[8];
	float working;
	float chunk;
	struct timeval tv;
	struct gps_data_t gps_data;
	if ((rc = gps_open("localhost", "2947", &gps_data)) == -1) {
	    printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
	    return EXIT_FAILURE;
	}
	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
	while (gps_data.status != STATUS_FIX) {
		rc = gps_read(&gps_data);
	}
	//printf("latitude: %f, longitude: %f, speed: %f, timestamp: %lf\n", gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.speed, gps_data.fix.time); //EDIT: Replaced tv.tv_sec with gps_data.fix.time
	working = 380926 * (90 - gps_data.fix.latitude);
	chunk = floor(working / 753571);
	//printf("Lat Chunk: %f\n", chunk);
	location[0] = (char)chunk + 33;
	printf("%c", location[0]);
	working -= (chunk * 753571);
	chunk = floor(working / 8281);
	//printf("Lat Chunk: %f\n", chunk);
	location[1] = (char)chunk + 33;
	printf("%c", location[1]);
	working -= (chunk * 8281);
	chunk = floor(working / 91);
	//printf("Lat Chunk: %f\n", chunk);
	location[2] = (char)chunk + 33;
	printf("%c", location[2]);
	working -= (chunk * 91);
	chunk = floor(working);
	//printf("Lat Chunk: %f\n", chunk);
	location[3] = (char)chunk + 33;
	printf("%c", location[3]);
	// Longitude
	working = 190463 * (180 + gps_data.fix.longitude);
	chunk = floor(working / 753571);
	//printf("Lon Chunk: %f\n", chunk);
	location[4] = (char)chunk + 33;
	printf("%c", location[4]);
	working -= (chunk * 753571);
	chunk = floor(working / 8281);
	//printf("Lon Chunk: %f\n", chunk);
	location[5] = (char)chunk + 33;
	printf("%c", location[5]);
	working -= (chunk * 8281);
	chunk = floor(working / 91);
	//printf("Lon Chunk: %f\n", chunk);
	location[6] = (char)chunk + 33;
	printf("%c", location[6]);
	working -= (chunk * 91);
	chunk = floor(working);
	//printf("Lon Chunk: %f\n", chunk);
	location[7] = (char)chunk + 33;
	printf("%c", location[7]);

	/* When you are done... */
	gps_stream(&gps_data, WATCH_DISABLE, NULL);
	gps_close(&gps_data);
	return EXIT_SUCCESS;
}

