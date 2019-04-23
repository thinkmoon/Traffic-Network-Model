//
// Created by chauncey on 18-6-11.
//

#include "TrafficLight.h"

void TrafficLight::setAllRed() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            status[i][j] = false;
        }
    }
}

void TrafficLight::setAllGreen() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
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
            if (emStatus % 4 == 0) {
                status[0][5]=status[4][1]=1;
                status[2][5]=status[0][3]=0;
            } else if (emStatus % 4 == 1) {
                status[0][5]=status[0][3]=1;
                status[4][1]=status[2][5]=0;
            } else {
                status[0][5]=status[2][5]=1;
                status[4][1]=status[0][3]=0;
            }
            break;
        case 4:
            switch (emStatus) {
                case 1:
                    status[0][5]=status[4][1]=1;
                    status[6][3]=status[2][7]=0;
                    status[0][3]=status[2][5]=0;
                    status[6][1]=status[4][7]=0;
                    break;
                case 2:
                    status[0][5]=status[4][1]=0;
                    status[6][3]=status[2][7]=1;
                    status[0][3]=status[2][5]=0;
                    status[6][1]=status[4][7]=0;
                    break;
                case 3:
                    status[0][5]=status[4][1]=0;
                    status[6][3]=status[2][7]=0;
                    status[0][3]=status[2][5]=1;
                    status[6][1]=status[4][7]=0;
                    break;
                case 4:
                    status[0][5]=status[4][1]=0;
                    status[6][3]=status[2][7]=0;
                    status[0][3]=status[2][5]=0;
                    status[6][1]=status[4][7]=1;
                case 5:
                    status[6][1]=status[4][1]=1;
                    status[6][3]=status[0][3]=0;
                    status[0][5]=status[2][5]=0;
                    status[2][7]=status[4][7]=0;
                    break;
                case 6:
                    status[6][1]=status[4][1]=0;
                    status[6][3]=status[0][3]=1;
                    status[0][5]=status[2][5]=0;
                    status[2][7]=status[4][7]=0;
                    break;
                case 7:
                    status[6][1]=status[4][1]=0;
                    status[6][3]=status[0][3]=0;
                    status[0][5]=status[2][5]=1;
                    status[2][7]=status[4][7]=0;
                    break;
                case 8:
                    status[6][1]=status[4][1]=0;
                    status[6][3]=status[0][3]=0;
                    status[0][5]=status[2][5]=0;
                    status[2][7]=status[4][7]=1;
                    break;
                case 9:
                    status[6][1]=status[6][3]=1;
                    status[0][5]=status[0][3]=0;
                    status[2][7]=status[2][5]=0;
                    status[4][1]=status[4][7]=0;
                    break;
                case 10:
                    status[6][1]=status[6][3]=0;
                    status[0][5]=status[0][3]=1;
                    status[2][7]=status[2][5]=0;
                    status[4][1]=status[4][7]=0;
                    break;
                case 11:
                    status[6][1]=status[6][3]=0;
                    status[0][5]=status[0][3]=0;
                    status[2][7]=status[2][5]=1;
                    status[4][1]=status[4][7]=0;
                    break;
                case 12:
                    status[6][1]=status[6][3]=0;
                    status[0][5]=status[0][3]=0;
                    status[2][7]=status[2][5]=0;
                    status[4][1]=status[4][7]=1;
                    break;
            }
    }

}

void TrafficLight::clock(int time) {
    emStatus = time % 12 +1;
    changeStatus();
}
void TrafficLight::addWait(int from, int to) {
    wait[from][to]++;
}
void TrafficLight::subWait(int from, int to) {
    if(wait[from][to] > 0) {
        wait[from][to]--;
    }
}
bool TrafficLight::getStatus(int from, int to) {
    int from_site=-1, to_site=-1;
    for (int i = 0; i < 8; i++) {
        if (from == roadID[i]) {
            from_site = i;
        } else if (to == roadID[i]) {
            to_site = i;
        }
    }
    if(from_site == -1 || to_site == -1){
        cout << RED << "TrafficLight::getStatus判断异常" << endl << "未找到对应的交通灯,程序出错被迫终止" << endl;
        cout << BLUE << from << " -> " << to << endl;
        exit(1);
    }
    if(status[from_site][to_site] == 1){
        return true;
    }else if(status[from_site][to_site] == 0){
        cout << RED << "从" << from_site << "方向转至" << to_site << "方向,通行状态" << status[from_site][to_site] << endl;
        return false;
    }else{
        cout << RED << "从" << from_site << "方向转至" << to_site << "方向,通行状态" << status[from_site][to_site] << endl;
        throw "禁止通行!遇到不可通行状态";
    }
}
TrafficLight::TrafficLight() {
    status[2][1] = status[4][3] = status[6][5] = status[0][7] = 1;
    for(int i = 0; i < 8 ; i++){
        // 初始化road
        roadID[i] = -1;
        // 出口不能进去
        status[1][i] = status[3][i] = status[5][i] = status[7][i] = -1;
        if(i%2 == 0){
            // 不能自转和变道
            status[0][i] = status[2][i] = status[4][i] = status[6][i] = -1;
            // 同向转道不受交通灯的控制
            status[i][i+1] = 1;
        }
    }
}
