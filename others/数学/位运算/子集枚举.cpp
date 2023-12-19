    // 枚举子集
    for (int i = 0; i < (1 << n); i++) {
        for (int j = i; ; j = (j - 1) & i) {

            if (j == 0) break;
        }
    }
    
    // 枚举父集
    for (int i = 0; i < (1 << n); i++) {
        for (int j = i; j < (1 << n); j = (j + 1) | i) {

        }
    }
