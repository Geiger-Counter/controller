#include <stdio.h>
#include "./../src/LinkedList.h"

int main() {

        LinkedList<long> elements = LinkedList<long>();

        for (int i = 0; i < 998; i++) {
            elements.add(i * 1000);
        }

        printf("No. 950: %ld\n", elements.get(950));

        for (int i = 998; i < 1100; i++) {
            elements.add(i * 1000);
            if(elements.size() > 999) {
                elements.shift();
            }
        }

        printf("No. 1050: %ld\n", elements.get(1050));

        elements.shift();

        printf("No. 0: %ld\n", elements.get(0));

}