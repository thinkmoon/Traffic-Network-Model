//
// Created by chauncey on 18-6-11.
//

#include "TrafficLight.h"

void TrafficLight::setAllRed() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            status[i][j] = false;
        }
    }
}

void TrafficLight::setAllGreen() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            status[i][j] = true;
        }
    }
}

void TrafficLight::changeStatus() {
    switch (type) {
        case 0:
            setAllGreen();
            break;
        case 1:
            setAllGreen();
            break;
        case 2:
            setAllGreen();
            break;
        case 3:
            if (emStatus == 1) {
                status[2][0] = status[0][2] = true;
                status[1][0] = status[2][1] = false;
            } else if (emStatus == 2) {
                status[1][0] = status[2][0] = true;
                status[0][2] = status[2][1] = false;
            } else if (emStatus == 3) {
                status[2][1] = status[2][0] = true;
                status[0][2] = status[1][0] = false;
            } else {
                status[0][1] = status[0][2] = false;
                status[1][0] = status[1][2] = false;
                status[2][0] = status[2][0] = false;
                return;
            }
            status[0][1] = status[1][2] = true;
            break;
        case 4:
            setAllRed();
            status[0][1] = status[1][2] = status[2][3] = status[3][0] = true;
            if (emStatus == 1) {
                status[1][0] = status[3][0] = true;
            } else if (emStatus == 2) {
                status[2][1] = status[3][1] = true;
            } else if (emStatus == 3) {
                status[0][2] = status[3][2] = true;
            } else if (emStatus == 4) {
                status[0][3] = status[1][3] = true;
            } else if (emStatus == 5) {
                status[3][1] = status[1][3] = true;
            } else if (emStatus == 6) {
                status[0][2] = status[2][0] = true;
            } else if (emStatus == 7) {
                status[0][3] = status[2][1] = true;
            } else if (emStatus == 8) {
                status[2][3] = status[0][1] = true;
            }
    }

}

void TrafficLight::clock(int time) {
    emStatus = time / 3 % 7 + 1;
    changeStatus();
}

bool TrafficLight::getStatus(int from, int to) {
    cout << " from " << from << "to " << to << endl;
    int from_site, to_site;
    for (int i = 0; i < 8; i++) {
        if (from == roadID[i]) {
            from_site = i;
        } else if (to == roadID[i]) {
            to_site == i;
        }
        cout << " " << roadID[i];
    }
    cout << "fromsite:" << from_site << " to_site" << to_site << endl;
    return status[from_site][to_site];
}
