#define lsb0_3mask_8bit     0x0f             //                               0000 1111 in binary
#define lsb4_7mask_8bit     0xf0             //                               1111 0000 in binary
#define lsb4_9mask_16bit    0x03f0           //                     0000 0011 1111 0000 in binary
#define lsb10_11mask_16bit  0x0c00           //                     0000 1100 0000 0000 in binary
#define lsb12_15mask_16bit  0xf000           //                     1111 0000 0000 0000 in binary
#define lsb16_18mask_32bit  0x00070000       // 0000 0000 0000 0111 0000 0000 0000 0000 in binary
#define lsb19_19mask_32bit  0x00080000       // 0000 0000 0000 1000 0000 0000 0000 0000 in binary
#define lsb20_21mask_32bit  0x00300000       // 0000 0000 0011 0000 0000 0000 0000 0000 in binary
#define lsb22_23mask_32bit  0x00c00000       // 0000 0000 1100 0000 0000 0000 0000 0000 in binary

#define safe_clear6_8bit(n)  (n & 0xfc30ffff)// 1111 1100 0011 0000 1111 1111 1111 1111 in binary
#define safe_clear6_10bit(n) (n & 0xf030ffff)// 1111 0000 0011 0000 1111 1111 1111 1111 in binary
#define safe_clear6_12bit(n) (n & 0xf030fff3)// 1111 0000 0011 0000 1111 1111 1111 0011 in binary
#define safe_clear7_4bit(n)  (n & 0xfffffff0)// 1111 1111 1111 1111 1111 1111 1111 0000 in binary
#define safe_clear7_8bit(n)  (n & 0xfffcf3f0)// 1111 1111 1111 1100 1111 0011 1111 0000 in binary
#define safe_clear9_4bit(n)  (n & 0xfffffe8f)// 1111 1111 1111 1111 1111 1110 1000 1111 in binary 

void set_8bit(uint8_t mode) {
  const int pins[8] = {23, 22, 16, 17, 15, 14, 18, 19};
  for (int i = 0; i < 8; i++)
    pinMode(pins[i], mode);
}

inline uint8_t read_8bit() {
  uint32_t data = GPIO6_DR;
  return ((data >> 16) & lsb0_3mask_8bit) | ((data >> 18) & lsb4_7mask_8bit);
}

inline void write_8bit(uint8_t data) {
  GPIO6_DR  = ((data & lsb0_3mask_8bit) << 16) | ((data & lsb4_7mask_8bit) << 18);
}

inline void safe_write_8bit(uint8_t data) {
  GPIO6_DR = safe_clear6_8bit(GPIO6_DR) | ((data & lsb0_3mask_8bit) << 16) | ((data & lsb4_7mask_8bit) << 18);
}

void set_10bit(uint8_t mode) {
  const int pins[10] = {21, 20, 23, 22, 16, 17, 15, 14, 18, 19};
  for (int i = 0; i < 10; i++)
    pinMode(pins[i], mode);
}

inline uint16_t read_10bit() {
  uint32_t data = GPIO6_DR;
  return ((data >> 16) & lsb0_3mask_8bit) | ((data >> 18) & lsb4_9mask_16bit);
}

inline void write_10bit(uint16_t data) {
  GPIO6_DR = ((data & lsb0_3mask_8bit) << 16) | ((data & lsb4_9mask_16bit) << 18);
}

inline void safe_write_10bit(uint16_t data) {
  GPIO6_DR = safe_clear6_10bit(GPIO6_DR) | ((data & lsb0_3mask_8bit) << 16) | ((data & lsb4_9mask_16bit) << 18);
}

void set_12bit(uint8_t mode) {
  const int pins[12] = {0, 1, 21, 20, 23, 22, 16, 17, 15, 14, 18, 19};
  for (int i = 0; i < 12; i++)
    pinMode(pins[i], mode);
}

inline uint16_t read_12bit() {
  uint32_t data = GPIO6_DR;
  return ((data >> 16) & lsb0_3mask_8bit) | ((data >> 18) & lsb4_9mask_16bit) | ((data << 8) & lsb10_11mask_16bit);
}

inline void write_12bit(uint16_t data) {
  GPIO6_DR = ((data & lsb0_3mask_8bit) << 16) | ((data & lsb4_9mask_16bit) << 18) | ((data & lsb10_11mask_16bit) >> 8);
}

inline void safe_write_12bit(uint16_t data) {
  GPIO6_DR = safe_clear6_12bit(GPIO6_DR) | ((data & lsb0_3mask_8bit) << 16) | ((data & lsb4_9mask_16bit) << 18) | ((data & lsb10_11mask_16bit) >> 8);
}

void set_16bit(uint8_t mode) {
  const int pins[16] = { 15, 14, 18, 19, 0, 1, 21, 20, 23, 22, 16, 17, 13, 11, 12, 10};
  for (int i = 0; i < 16; i++)
    pinMode(pins[i], mode);
}

inline uint16_t read_16bit() {
  uint32_t data0 = GPIO6_DR;
  uint32_t data1 = GPIO7_DR;
  return (data1 & lsb0_3mask_8bit) | ((data0 >> 18) & lsb4_9mask_16bit) | ((data0 << 8) & lsb10_11mask_16bit) | ((data0 >> 4) & lsb12_15mask_16bit);
}

inline void write_16bit(uint16_t data) {
  GPIO6_DR = ((data & lsb4_9mask_16bit) << 18) | ((data & lsb10_11mask_16bit) >> 8) | ((data & lsb12_15mask_16bit) << 4);
  GPIO7_DR = (data & lsb0_3mask_8bit);
}

inline void safe_write_16bit(uint16_t data) {
  GPIO6_DR = safe_clear6_12bit(GPIO6_DR) | ((data & lsb4_9mask_16bit) << 18) | ((data & lsb10_11mask_16bit) >> 8) | ((data & lsb12_15mask_16bit) << 4);
  GPIO7_DR = safe_clear7_4bit(GPIO7_DR)  |  (data & lsb0_3mask_8bit);
}

void set_24bit(uint8_t mode) {
  const int pins[24] = {7, 8, 9, 6, 5, 4, 3, 2, 15, 14, 18, 19, 0, 1, 21, 20, 23, 22, 16, 17, 13, 11, 12, 10};
  for (int i = 0; i < 24; i++)
    pinMode(pins[i], mode);
}

inline uint32_t read_24bit() {
  uint32_t data0 = GPIO6_DR;
  uint32_t data1 = GPIO7_DR;
  uint32_t data2 = GPIO9_DR;
  return (data1 & lsb0_3mask_8bit) | ((data0 >> 18) & lsb4_9mask_16bit) | ((data0 << 8) & lsb10_11mask_16bit) | ((data0 >> 4) & lsb12_15mask_16bit) | ((data2 << 12) & lsb16_18mask_32bit) | ((data2 << 11) & lsb19_19mask_32bit) | ((data1 << 10) & lsb20_21mask_32bit) | ((data1 << 6) & lsb22_23mask_32bit);
}

inline void write_24bit(uint32_t data) {
  GPIO6_DR = ((data & lsb4_9mask_16bit) << 18)   | ((data & lsb10_11mask_16bit) >> 8)  | ((data & lsb12_15mask_16bit) << 4);
  GPIO7_DR = (data & lsb0_3mask_8bit)            | ((data & lsb20_21mask_32bit) >> 10) | ((data & lsb22_23mask_32bit) >> 6);
  GPIO9_DR = ((data & lsb16_18mask_32bit) >> 12) | ((data & lsb19_19mask_32bit) >> 11);
}

inline void safe_write_24bit(uint32_t data) {
  GPIO6_DR = safe_clear6_12bit(GPIO6_DR) | ((data & lsb4_9mask_16bit) << 18)   | ((data & lsb10_11mask_16bit) >> 8)  | ((data & lsb12_15mask_16bit) << 4);
  GPIO7_DR = safe_clear7_8bit(GPIO7_DR)  | (data & lsb0_3mask_8bit)            | ((data & lsb20_21mask_32bit) >> 10) | ((data & lsb22_23mask_32bit) >> 6);
  GPIO9_DR = safe_clear9_4bit(GPIO9_DR)  | ((data & lsb16_18mask_32bit) >> 12) | ((data & lsb19_19mask_32bit) >> 11);
}

//example code to cycle through all the 24 pins one after the other
void setup() {
  set_24bit(OUTPUT);
}

void loop() {
  uint32_t data = 1;
  for(int i=0; i<24; i++){
    safe_write_24bit(data<<i);
    delay(500);
  }
}
