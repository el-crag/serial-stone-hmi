#include "Stone.hpp"

bool Stone::parse(Receive &receive, const unsigned char * STONE_RX_BUF, size_t length) {
	//STONE_RX_CNT>11 The legal instruction length is at least 14, and the last two expressions verify the end of the frame and CRC checksum
	if (length < 14) {
		// this is an error
		return false;
	}

	// instruction must start with header
	if (strncmp(STONE_RX_BUF, "ST<", 3) != 0) {
		return false;
	}

	// find position of tail
	const char * tail = strstr(STONE_RX_BUF, ">ET");
	if (tail == nullptr) {
		return false;
	}

	// start position of tail
	size_t STONE_RX_CNT = tail - STONE_RX_BUF + 4;

	if (Stone::crc(STONE_RX_BUF, STONE_RX_CNT) != 0) {
		return false;
	}

	receive.cmd = (unsigned int) STONE_RX_BUF[3];

	Stone::parseCmd(receive, STONE_RX_BUF[3], STONE_RX_CNT - 3);

	STONE_RX_CNT = 0;  //Data legal counter is cleared

	// Done
	return true;
}

uint16_t Stone::crc(const unsigned char *buf, unsigned int len) {
	unsigned int i;
	unsigned short crc = 0xFFFF;

	unsigned char * crc_idx = ptr + len - 2;
	unsigned char swap;
	swap = *crc_idx;
	*crc_idx = *(crc_idx + 1);
	*(crc_idx + 1) = swap;

	while (len--) {
		crc ^= *ptr++;
		for (i = 0; i < 8; ++i) {
			if (crc & 1) {
				crc = (crc >> 1) ^ 0xA001;
			}
			else {
				crc = (crc >> 1);
			}
		}
	}

	return crc;
}

void Stone::parseCmd(Receive &receive, const unsigned char *buffer, size_t length) {
	switch (receive.cmd) {
		case STONE_sys_state: {
			Stone::initData(receive.data, receive.len + 1); //Memory is allocated one byte too much
			sscanf((const char*) STONE_RX_BUF + 7, "%[^>ET]", receive.data);

			break;
		}
	}
}
