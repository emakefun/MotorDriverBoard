enum PINS {
    //% block="S1"
    S1,
    //% block="S2"
    S2,
    //% block="S3"
    S3,
    //% block="S4"
    S4,
    //% block="S5"
    S5,
    //% block="S6"
    S6,
    //% block="S7"
    S7,
    //% block="S8"
    S8
}

enum SERVOS {
    //% block="S1"
    S1 = 1,
    //% block="S2"
    S2,
    //% block="S3"
    S3,
    //% block="S4"
    S4,
    //% block="S5"
    S5,
    //% block="S6"
    S6,
    //% block="S7"
    S7,
    //% block="S8"
    S8
}

enum LEVELS {
    //% block="HIGH"
    HIGH,
    //% block="LOW"
    LOW
}

enum MOTORS {
    //% block="M1"
    M1 = 1,
    //% block="M2"
    M2,
    //% block="M3"
    M3,
    //% block="M4"
    M4
}

enum DIRECTIONS {
    //% block="FORWARD"
    FORWARD,
    //% block="BACKWARD"
    BACKWARD,
    //% block="BRAKE"
    BRAKE,
    //% block="RELEASE"
    RELEASE
}

enum STEPPER_DIRECTIONS {
    //% block="FORWARD"
    FORWARD,
    //% block="BACKWARD"
    BACKWARD
}

enum ENCODERS {
    //% block="Encoder1"
    Encoder1 = 1,
    //% block="Encoder2"
    Encoder2,
    //% block="Encoder3"
    Encoder3,
    //% block="Encoder4"
    Encoder4
}

enum STEPPERS {
    //% block="Stepper1"
    Stepper1 = 1,
    //% block="Stepper2"
    Stepper2
}

enum MODES {
    //% block="DOUBLE"
    DOUBLE = 1,
    //% block="SINGLE"
    SINGLE,
    //% block="INTERLEAVE"
    INTERLEAVE
}

//% color="#66A569" iconWidth=50 iconHeight=40
namespace MotorDriverBoard {

    //% block="MotorDriverBoard initialization" blockType="command"
    export function init(parameter: any, block: any) {
        Generator.addInclude('Emakefun_MotorDriver', '#include<Emakefun_MotorDriver.h>', true);
        Generator.addObject('mMotorDriver', 'Emakefun_MotorDriver', 'mMotorDriver = Emakefun_MotorDriver(0x60);', true);
        Generator.addSetupMainTop('Serial.begin', 'Serial.begin(9600);', true);
    }

    //% block="set the IO frequency to [FREQ]" blockType="command"
    //% FREQ.shadow="range" FREQ.params.min=1 FREQ.params.max=1600 FREQ.defl=1000
    export function setIOFrequency(parameter: any, block: any) {
        let freq = parameter.FREQ.code;
        Generator.addSetup('mMotorDriver.begin', `mMotorDriver.begin(${freq});`, true);
    }

    //% block="set the IO [PIN] to [LEVEL]" blockType="command"
    //% PIN.shadow="dropdown" PIN.options="PINS" PIN.defl="PINS.S1"
    //% LEVEL.shadow="dropdown" LEVEL.options="LEVELS" LEVEL.defl="LEVELS.HIGH"
    export function setIOPinLevel(parameter: any, block: any) {
        let pin = parameter.PIN.code;
        let level = parameter.LEVEL.code;
        Generator.addSetup(`mMotorDriver.setIOPinLevel${pin}`, `mMotorDriver.setPin(${pin}, ${level});`, true);
    }

    //% block="set the IO [PIN] output PWM value(0-4096) [PWM]" blockType="command"
    //% PIN.shadow="dropdown" PIN.options="PINS" PIN.defl="PINS.S1"
    //% PWM.shadow="range" PWM.params.min=0 PWM.params.max=4096 PWM.defl=1024
    export function setIOPinPwm(parameter: any, block: any) {
        let pin = parameter.PIN.code;
        let pwm = parameter.PWM.code;
        Generator.addSetup(`mMotorDriver.setIOPinPwm${pin}`, `mMotorDriver.setPin(${pin}, ${pwm});`, true);
    }

    //% block="DC motor initialization [MOTOR]" blockType="command"
    //% MOTOR.shadow="dropdown" MOTOR.options="MOTORS" MOTOR.defl="MOTORS.M1"
    export function initDCMotor(parameter: any, block: any) {
        let motorValue = MOTORS[parameter.MOTOR.code];
        Generator.addObject(`mMotorDriver.DCmotor_${motorValue}`, 'Emakefun_DCMotor', `*DCmotor_${motorValue} = mMotorDriver.getMotor(${motorValue});`, true);
        Generator.addSetup(`mMotorDriver.begin`, `mMotorDriver.begin(150);`, true);
    }

    //% block="DC Motor [MOTOR] Direction [DIRECTION] Speed (0-255) [SPEED]" blockType="command"
    //% MOTOR.shadow="dropdown" MOTOR.options="MOTORS" MOTOR.defl="MOTORS.M1"
    //% DIRECTION.shadow="dropdown" DIRECTION.options="DIRECTIONS" DIRECTION.defl="DIRECTIONS.FORWARD"
    //% SPEED.shadow="range" SPEED.params.min=0 SPEED.params.max=255 SPEED.defl=0
    export function controlDCMotor(parameter: any, block: any) {
        let motorValue = MOTORS[parameter.MOTOR.code];
        let direction = parameter.DIRECTION.code;
        let speed = parameter.SPEED.code;
        Generator.addCode(`DCmotor_${motorValue}->run(${direction});`);
        Generator.addCode(`DCmotor_${motorValue}->setSpeed(${speed});`);
    }

    //% block="Stop DC motor [MOTOR]" blockType="command"
    //% MOTOR.shadow="dropdown" MOTOR.options="MOTORS" MOTOR.defl="MOTORS.M1"
    export function stopDCMotor(parameter: any, block: any) {
        let motorValue = MOTORS[parameter.MOTOR.code];
        Generator.addCode(`DCmotor_${motorValue}->run(BRAKE);`);
    }

    //% block="Encoder motor initialization [ENCODER]" blockType="command"
    //% ENCODER.shadow="dropdown" ENCODER.options="ENCODERS" ENCODER.defl="ENCODERS.Encoder1"
    export function initEncoderMotor(parameter: any, block: any) {
        let encoderValue = ENCODERS[parameter.ENCODER.code];
        Generator.addObject(`mMotorDriver.EncodeMotor_${encoderValue}`, 'Emakefun_EncoderMotor', `*EncodeMotor_${encoderValue} = mMotorDriver.getEncoderMotor(E${encoderValue});`, true);
    }

    //% block="Encoder Motor [ENCODER] Direction [DIRECTION] Speed (0-255) [SPEED]" blockType="command"
    //% ENCODER.shadow="dropdown" ENCODER.options="ENCODERS" ENCODER.defl="MOTORS.Encoder1"
    //% DIRECTION.shadow="dropdown" DIRECTION.options="DIRECTIONS" DIRECTION.defl="DIRECTIONS.FORWARD"
    //% SPEED.shadow="range" SPEED.params.min=0 SPEED.params.max=255 SPEED.defl=0
    export function controlEncoderMotor(parameter: any, block: any) {
        let encoderValue = ENCODERS[parameter.ENCODER.code];
        let direction = parameter.DIRECTION.code;
        let speed = parameter.SPEED.code;
        Generator.addCode(`EncodeMotor_${encoderValue}->run(${direction});`);
        Generator.addCode(`EncodeMotor_${encoderValue}->setSpeed(${speed});`);
    }

    //% block="Stop Encoder Motor [ENCODER]" blockType="command"
    //% ENCODER.shadow="dropdown" ENCODER.options="ENCODERS" ENCODER.defl="MOTORS.Encoder1"
    export function stopEncoderMotor(parameter: any, block: any) {
        let encoderValue = ENCODERS[parameter.ENCODER.code];
        Generator.addCode(`EncodeMotor_${encoderValue}->run(BRAKE);`);
    }

    //% block="Stepper motor initialization [STEPPER] Number of steps (steps/lap) [STEP] Revolutions per minute [LAP]" blockType="command"
    //% STEPPER.shadow="dropdown" STEPPER.options="STEPPERS" STEPPER.defl="STEPPERS.Stepper1"
    //% STEP.shadow="range" STEP.params.min=0 STEP.params.max=255 STEP.defl=100
    //% LAP.shadow="range" LAP.params.min=0 LAP.params.max=255 LAP.defl=200
    export function initStepperMotor(parameter: any, block: any) {
        let stepperValue = STEPPERS[parameter.STEPPER.code];
        let step = parameter.STEP.code;
        let lap = parameter.LAP.code;
        Generator.addObject(`mMotorDriver.StepperMotor_${stepperValue}`, 'Emakefun_StepperMotor', `*StepperMotor_${stepperValue} = mMotorDriver.getStepper(${stepperValue}, ${step});`, true);
        Generator.addCode(`StepperMotor_${stepperValue}->setSpeed(${lap});`);
    }

    //% block="Stepper motor [STEPPER] Direction [DIRECTION] Drive mode (half-step/single-step) [MODE] Number of steps [STEP]" blockType="command"
    //% STEPPER.shadow="dropdown" STEPPER.options="STEPPERS" STEPPER.defl="STEPPERS.Stepper1"
    //% DIRECTION.shadow="dropdown" DIRECTION.options="STEPPER_DIRECTIONS" DIRECTION.defl="STEPPER_DIRECTIONS.FORWARD"
    //% MODE.shadow="dropdown" MODE.options="MODES" MODE.defl="MODES.DOUBLE"
    //% STEP.shadow="range" STEP.params.min=0 STEP.params.max=255 STEP.defl=100
    export function controlStepperMotor(parameter: any, block: any) {
        let stepperValue = STEPPERS[parameter.STEPPER.code];
        let direction = parameter.DIRECTION.code;
        let mode = parameter.MODE.code;
        let step = parameter.STEP.code;
        Generator.addCode(`StepperMotor_${stepperValue}->step(${step}, ${direction}, ${mode});`);
    }

    //% block="Stop stepper motor [STEPPER]" blockType="command"
    //% STEPPER.shadow="dropdown" STEPPER.options="STEPPERS" STEPPER.defl="STEPPERS.Stepper1"
    export function stopStepperMotor(parameter: any, block: any) {
        let stepperValue = STEPPERS[parameter.STEPPER.code];
        Generator.addCode(`StepperMotor_${stepperValue}->release();`);
    }

    //% block="Servo initialization interface [SERVO]" blockType="command"
    //% SERVO.shadow="dropdown" SERVO.options="SERVOS" SERVO.defl="SERVOS.S1"
    export function initServoMotor(parameter: any, block: any) {
        let servoValue = SERVOS[parameter.SERVO.code];
        Generator.addObject(`mMotorDriver.servo${servoValue}`, 'Emakefun_Servo', `*servo${servoValue} = mMotorDriver.getServo(${servoValue});`, true);
        Generator.addSetup(`mMotorDriver.begin`, `mMotorDriver.begin(50);`, true);
    }

    //% block="The servo interface [SERVO] reads the current servo angle" blockType="command"
    //% SERVO.shadow="dropdown" SERVO.options="SERVOS" SERVO.defl="SERVOS.S1"
    export function readServoMotorAngle(parameter: any, block: any) {
        let servoValue = SERVOS[parameter.SERVO.code];
        Generator.addCode(`servo${servoValue}->readDegrees();`);
    }

    //% block="Servo Interface [SERVO] Angle [ANGLE] Speed(0-100) [SPEED]" blockType="command"
    //% SERVO.shadow="dropdown" SERVO.options="SERVOS" SERVO.defl="SERVOS.S1"
    //% ANGLE.shadow="range" ANGLE.params.min=0 ANGLE.params.max=180 ANGLE.defl=90
    //% SPEED.shadow="range" SPEED.params.min=0 SPEED.params.max=10 SPEED.defl=10
    export function controlServoMotor(parameter: any, block: any) {
        let servoValue = SERVOS[parameter.SERVO.code];
        let angle = parameter.ANGLE.code;
        let speed = parameter.SPEED.code;
        Generator.addCode(`servo${servoValue}->writeServo(${angle}, ${speed});`);
    }

}
