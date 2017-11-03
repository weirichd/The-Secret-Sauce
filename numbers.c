static const unsigned char numbers[3*5*10] = {1, 1, 1, // 0
                                              1, 0, 1,
                                              1, 0, 1,
                                              1, 0, 1,
                                              1, 1, 1,

                                              1, 1, 0, // 1
                                              0, 1, 0,
                                              0, 1, 0,
                                              0, 1, 0,
                                              1, 1, 1,

                                              1, 1, 1, // 2
                                              0, 0, 1,
                                              1, 1, 1,
                                              1, 0, 0,
                                              1, 1, 1,

                                              1, 1, 1, // 3
                                              0, 0, 1,
                                              1, 1, 1,
                                              0, 0, 1,
                                              1, 1, 1,

                                              1, 0, 1, // 4
                                              1, 0, 1,
                                              1, 1, 1,
                                              0, 0, 1,
                                              0, 0, 1,

                                              1, 1, 1, // 5
                                              1, 0, 0,
                                              1, 1, 1,
                                              0, 0, 1,
                                              1, 1, 1,

                                              1, 1, 1, // 6
                                              1, 0, 0,
                                              1, 1, 1,
                                              1, 0, 1,
                                              1, 1, 1,

                                              1, 1, 1, // 7
                                              0, 0, 1,
                                              0, 0, 1,
                                              0, 0, 1,
                                              0, 0, 1,

                                              1, 1, 1, // 8
                                              1, 0, 1,
                                              1, 1, 1,
                                              1, 0, 1,
                                              1, 1, 1,

                                              1, 1, 1, // 9
                                              1, 0, 1,
                                              1, 1, 1,
                                              0, 0, 1,
                                              0, 0, 1};


void copy_number_into_buffer(int *buffer, int number, int x, int y, int width) {
    int digits[15] = {}; // Large enougth for 32 bit ints

    for(int i = 0; i < 15; i++) {
       digits[i] = number % 10; 
       number /= 10;
    }

    int place = 0;
    for(int j = 14; j >= 0; j--) {
        int digit = digits[j];

        for(int i = 0; i < 15; i++) {
            int x_offset = i % 3 + x + place * 5;
            int y_offset = i / 3 + y;
            if(numbers[digit * 15 + i]) {
                buffer[y_offset * width + x_offset] = 0xFFFFFFFF;
            } else {
                buffer[y_offset * width + x_offset] = 0xFF000000;
            }
        }
        place++;
    }
}
