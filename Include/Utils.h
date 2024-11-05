//
// Created by Amaury Paillard on 05/11/2024.
//

#ifndef UTILS_H
#define UTILS_H


namespace Utils {
    inline char *generateName(int n) {
        static char name[12] = {};

        if (n <= 9) {
            name[0] = static_cast<char>('0' + n);
            name[1] = '\0';
        } else {
            n -= 10;

            const int letterOffset = n / 9;
            const char letterPrefix = static_cast<char>('A' + letterOffset);
            const int numberSuffix = n % 9 + 1;

            name[0] = letterPrefix;
            name[1] = static_cast<char>('0' + numberSuffix);
            name[2] = '\0';
        }

        return name;
    }
}

#endif //UTILS_H
