//
// Created by chauncey on 18-6-11.
//

#include "TrafficLight.h"

void TrafficLight::setAllRed() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            status[i][j] = 0;
        }
    }
}

void TrafficLight::setAllGreen() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            status[i][j] = 1;
        }
    }
}

void TrafficLight::changeStatus() {
    switch (type) {
        case 3:
            this->setType(3);
            if (emStatus == 1) {
                status[0][5] = 1;
            } else if (emStatus == 2) {
                status[6][1] = 1;
            } else {
                status[4][7] = 1;
            }
            break;
        case 4:
            this->setType(4);
            switch (emStatus) {
                case 1:
//                    平衡左右
                    status[0][5] = status[4][1] = 1;
                    break;
                case 2:
//                    平衡上下
                    status[6][3] = status[2][7] = 1;
                    break;
                case 3:
                    status[0][3] = status[4][7] = 1;
                    break;
                case 4:
                    status[6][1] = status[2][5] = 1;
                case 5:
                    status[6][1] = status[4][1] = 1;
                    break;
                case 6:
                    status[6][3] = status[0][3] = 1;
                    break;
                case 7:
                    status[0][5] = status[2][5] = 1;
                    break;
                case 8:
                    status[2][7] = status[4][7] = 1;
                    break;
                case 9:
                    status[6][1] = status[6][3] = 1;
                    break;
                case 10:
                    status[0][5] = status[0][3] = 1;
                    break;
                case 11:
                    status[2][7] = status[2][5] = 1;
                    break;
                case 12:
                    status[4][1] = status[4][7] = 1;
                    break;
            }
    }
}

void TrafficLight::clock(int time) {
    switch (this->type) {
        case 3:
            if (wait[0][5] > wait[4][7] && wait[0][5] > wait[6][1]) {
                emStatus = 1;
            }else if(wait[6][1] > wait[4][7] && wait[6][1]> wait[0][5]) {
                emStatus = 2;
            } else if(wait[4][7] > wait[6][1] && wait[4][7]> wait[0][5]){
                emStatus = 3;
            } else {
                emStatus = time % 3 + 1;
            }
            break;
        case 4:
            emStatus = time % 12 + 1;
            break;
    }
    changeStatus();
}

void TrafficLight::addWait(int from, int to, int weight) {
    int from_site = mp.find(from)->second, to_site = mp.find(to)->second;
    wait[from_site][to_site]+=weight;
}

void TrafficLight::subWait(int from, int to, int weight, int value) {
    int from_site = mp.find(from)->second, to_site = mp.find(to)->second;
    wait[from_site][to_site]-=weight*value;
}

bool TrafficLight::getStatus(int from, int to) {
    int from_site = mp.find(from)->second, to_site = mp.find(to)->second;
    if (status[from_site][to_site] == 1) {
        cout << GREEN << "准备转向:" << from_site << "->" << to_site << endl;
        return true;
    } else if(from_site % 2 == to_site %2){
        cout << RED << "打算从" << from << "号路转向" << to << "号路" << endl;
        cout << RED << "准备转向:" << from_site << "->" << to_site << endl;
        cout << RED << "路口ID:" << ID << "不存在的状态";
        exit(1);
    }
    else {
        cout << RED << type << "路口，准备转向:" << from_site << "->" << to_site << endl;
        return false;
    }
}

void TrafficLight::setType(int type) {
    this->type = type;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            status[i][j] = -1;
        }
    }
    switch (type) {
        case 2:
            status[0][5] = status[4][1] = 1;
        case 3:
            status[0][7] = status[0][1] = status[4][1] = status[4][5] = status[6][7] = status[6][5] = 1;
            break;
        case 4:
            status[0][7] = status[0][1] = status[2][1] = status[2][3] = status[4][3] = status[4][5] = status[6][5] = status[6][7] = 1;
            break;
        default:
            break;
    }
}

TrafficLight::TrafficLight() {

}
