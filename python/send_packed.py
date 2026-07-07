import serial
import time

PORT = "COM5"
BAUD = 115200

HEADER_1 = 0xAA
HEADER_2 = 0x55
CRC8_POLY = 0x07
CRC8_INIT = 0x00

CMD_PING = 0x01
CMD_LED_SET = 0x02
CMD_GET_STATUS = 0x03


def crc8_calculate(data: bytes) -> int:
    crc = CRC8_INIT

    for byte in data:
        crc ^= byte

        for _ in range(8):
            if crc & 0x80:
                crc = ((crc << 1) ^ CRC8_POLY) & 0xFF
            else:
                crc = (crc << 1) & 0xFF

    return crc


def build_packet(command_type: int, payload: bytes = b"") -> bytes:
    packet_without_crc = bytes([
        HEADER_1,
        HEADER_2,
        len(payload),
        command_type
    ]) + payload

    crc = crc8_calculate(packet_without_crc)

    return packet_without_crc + bytes([crc])


def send_packet(packet: bytes):
    print("TX:", " ".join(f"{b:02X}" for b in packet))

    with serial.Serial(PORT, BAUD, timeout=1) as ser:
        ser.write(packet)
        time.sleep(0.1)

        response = ser.read(100)
        print("RX:", response)


# TEST 1: PING
packet = build_packet(CMD_PING)
send_packet(packet)

# TEST 2: LED ON
packet = build_packet(CMD_LED_SET, bytes([1]))
send_packet(packet)

# TEST 3: LED OFF
packet = build_packet(CMD_LED_SET, bytes([0]))
send_packet(packet)

# TEST 4: GET STATUS
packet = build_packet(CMD_GET_STATUS)
send_packet(packet)