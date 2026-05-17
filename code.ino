#include <Bluepad32.h>

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

//====== LEFT DRIVER ======
#define L_PWMA  21
#define L_AIN1  22
#define L_AIN2  23
#define L_BIN1  19
#define L_BIN2  18
#define L_PWMB  5

//====== RIGHT DRIVER ======
#define R_PWMA  13
#define R_AIN1  14
#define R_AIN2  12
#define R_BIN1  27
#define R_BIN2  26
#define R_PWMB  25

//====== STANDBY ======
#define STBY 33

// PWM Channels
#define CH_LA 0
#define CH_LB 1
#define CH_RA 2
#define CH_RB 3

#define PWM_FREQ 1000
#define PWM_RES 8

//==================================================
// CONTROLLER CONNECT CALLBACK
//==================================================

void onConnectedController(ControllerPtr ctl) {

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {

        if (myControllers[i] == nullptr) {

            Serial.println("Controller Connected!");
            myControllers[i] = ctl;
            break;
        }
    }
}

//==================================================
// CONTROLLER DISCONNECT CALLBACK
//==================================================

void onDisconnectedController(ControllerPtr ctl) {

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {

        if (myControllers[i] == ctl) {

            Serial.println("Controller Disconnected!");
            myControllers[i] = nullptr;
            stopMotors();
            break;
        }
    }
}

//==================================================
// SETUP
//==================================================


//==================================================
// LEFT SIDE DRIVE
//==================================================

void driveLeft(int speed) {

    bool forward = speed >= 0;

    if (!forward)
        speed = -speed;

    // MOTOR A
    digitalWrite(L_AIN1, forward);
    digitalWrite(L_AIN2, !forward);

    // MOTOR B
    digitalWrite(L_BIN1, forward);
    digitalWrite(L_BIN2, !forward);

    ledcWrite(CH_LA, speed);
    ledcWrite(CH_LB, speed);
}

//==================================================
// RIGHT SIDE DRIVE
//==================================================

void driveRight(int speed) {

    bool forward = speed >= 0;

    if (!forward)
        speed = -speed;

    // MOTOR A
    digitalWrite(R_AIN1, forward);
    digitalWrite(R_AIN2, !forward);

    // MOTOR B
    digitalWrite(R_BIN1, forward);
    digitalWrite(R_BIN2, !forward);

    ledcWrite(CH_RA, speed);
    ledcWrite(CH_RB, speed);
}

//==================================================
// STOP
//==================================================

void stopMotors() {

    ledcWrite(CH_LA, 0);
    ledcWrite(CH_LB, 0);
    ledcWrite(CH_RA, 0);
    ledcWrite(CH_RB, 0);
}


void setup() {

    Serial.begin(115200);

    // LEFT DRIVER PINS
    pinMode(L_AIN1, OUTPUT);
    pinMode(L_AIN2, OUTPUT);
    pinMode(L_BIN1, OUTPUT);
    pinMode(L_BIN2, OUTPUT);

    // RIGHT DRIVER PINS
    pinMode(R_AIN1, OUTPUT);
    pinMode(R_AIN2, OUTPUT);
    pinMode(R_BIN1, OUTPUT);
    pinMode(R_BIN2, OUTPUT);

    // STANDBY
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);

    // PWM SETUP
    ledcSetup(CH_LA, PWM_FREQ, PWM_RES);
    ledcAttachPin(L_PWMA, CH_LA);

    ledcSetup(CH_LB, PWM_FREQ, PWM_RES);
    ledcAttachPin(L_PWMB, CH_LB);

    ledcSetup(CH_RA, PWM_FREQ, PWM_RES);
    ledcAttachPin(R_PWMA, CH_RA);

    ledcSetup(CH_RB, PWM_FREQ, PWM_RES);
    ledcAttachPin(R_PWMB, CH_RB);

    // BLUPAD32 START
    BP32.setup(&onConnectedController, &onDisconnectedController);

    Serial.println("PS4 RC CAR READY");
}

//==================================================
// LOOP
//==================================================

void loop() {

    BP32.update();

    for (auto ctl : myControllers) {

        if (ctl && ctl->isConnected() && ctl->hasData()) {

            // LEFT JOYSTICK Y
            int throttle = ctl->axisY();

            // RIGHT JOYSTICK X
            int steering = ctl->axisRX();

            // DEADZONE
            if (abs(throttle) < 20) throttle = 0;
            if (abs(steering) < 20) steering = 0;

            // MAP VALUES
            throttle = map(throttle, -512, 512, 130, -130);          //speed
            steering = map(steering, -512, 512, -130, 130);          //speed

            // DIFFERENTIAL MIXING
            int leftSpeed  = throttle + steering;
            int rightSpeed = throttle - steering;

            // LIMIT
            leftSpeed  = constrain(leftSpeed, -80, 80);             ///==---
            rightSpeed = constrain(rightSpeed, -80, 80);            

            // DRIVE
            driveLeft(leftSpeed);
            driveRight(rightSpeed);

            // DEBUG
            Serial.print("Throttle: ");
            Serial.print(throttle);

            Serial.print(" Steering: ");
            Serial.print(steering);

            Serial.print(" Left: ");
            Serial.print(leftSpeed);

            Serial.print(" Right: ");
            Serial.println(rightSpeed);
        }
    }

    delay(20);
}
