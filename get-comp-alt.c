#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main() {
	int rc;
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
	working = log(gps_data.fix.altitude * 3.280839895) / log(1.002);
	chunk = floor(working / 91);
	printf("%c", (char)chunk + 33);
	working -= (chunk * 91);
	chunk = floor(working);
	printf("%c", (char)chunk + 33);

	/* When you are done... */
	gps_stream(&gps_data, WATCH_DISABLE, NULL);
	gps_close(&gps_data);
	return EXIT_SUCCESS;
}

