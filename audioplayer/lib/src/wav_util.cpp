#include <wav_util.h>

uint8_t GetWavContent(uint8_t* data) {
	uint32_t smplrt;

	//check if RIFF file
	if(data[0] == 'R' && data[1] == 'I' && data[2] == 'F' && data[3] == 'F') {
		Serial1.println("RIFF");
	}
	else {
		return 0;
	}

	//check if wave filetype
	if(data[8] == 'W' && data[9] == 'A' && data[10] == 'V' && data[11] == 'E') {
		Serial1.println("WAVE");
	}
	else {
		return 0;
	}

	GetValue(&smplrt, 24, 4, data);
	Serial1.println(smplrt, 10);

}

template <typename T> T GetValue(T* type, uint16_t offset, uint8_t n, uint8_t* data) {
	*type = 0;

	for(uint8_t i = 0; i < n; i++) {
		*type |= data[offset + i] << (i * 8);
	}

	return *type;
}