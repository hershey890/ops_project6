#define LED1 2
#define LED2 3
#define LED3 4
int incomingbyte = 0;
bool led1_on = false;
bool led2_on = false;
bool led3_on = false;
int button_press[100];
int sequence[100];
int num_presses = 0;
int round_length = 0;

void flash_wrong() {
  delay(500);
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  delay(500);
}

void flash_right() {
  delay(500);
  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED3, LOW);
  delay(500);
}

void flash_red() {
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  delay(100);
}

void flash_yellow() {
  digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED2, LOW);
  delay(100);
}

void flash_green() {
  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED3, LOW);
  delay(100);
}

bool compareChars(int correctArray[], int inputArray[], int n1, int n2){
  for(int i = 0; i < n1; i++)
  {
    if(correctArray[i] != inputArray[i])
      return false;
  }

  return true;
}

void displaySequence(int correctArray[], int n1)
{
  for(int i = 0; i < n1; i++)
  {
    if(correctArray[i] == 1)
      flash_red();
    else if(correctArray[i] == 2)
      flash_yellow();
    else if(correctArray[i] == 3)
      flash_green();
  }
}

int add_character() {
  int iLed_color = 0;
  int rand_number = random(3);
  switch(rand_number) {
    case 0:
      iLed_color = 1;
      break;
    case 1:
      iLed_color = 2;
      break;
    case 2:
      iLed_color = 3;
      break;
    default:
      iLed_color = 1;
      break;
  }
  return(iLed_color);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  sequence[round_length] = add_character();
  round_length++;
  displaySequence(sequence, round_length);
  delay(250);
}

void loop() {
  // put your main code here, to run repeatedly:
  incomingbyte = Serial.read();
  if(incomingbyte == 1) {
    digitalWrite(LED1, HIGH);
    if(!led1_on) {
      led1_on = true;
      //save that button 1 was pressed
      if(num_presses < round_length) {
        button_press[num_presses] = incomingbyte;
        num_presses++;
      }
    }
  }
  if(incomingbyte == 2) {
    digitalWrite(LED2, HIGH);
    if(!led2_on) {
      led2_on = true;
      //save that button 1 was pressed
      if(num_presses < round_length) {
        button_press[num_presses] = incomingbyte;
        num_presses++;
      }
    }
  }
  if(incomingbyte == 3) {
    digitalWrite(LED3, HIGH);
    if(!led3_on) {
      led3_on = true;
      //save that button 1 was pressed
      if(num_presses < round_length) {
        button_press[num_presses] = incomingbyte;
        num_presses++;
      }
    }
  }
  if(incomingbyte == 4) {
    digitalWrite(LED1, LOW);
    led1_on = false;
    if(num_presses >= round_length) {
      if(compareChars(sequence, button_press, round_length, round_length)) {
        flash_right();
        //code to progress to the next round
        sequence[round_length] = add_character();
        round_length++;
        displaySequence(sequence, round_length);
        num_presses = 0;
        delay(250);
      } else {
        flash_wrong();
        exit(0);
      }
    }
  }
  if(incomingbyte == 5) {
    digitalWrite(LED2, LOW);
    led2_on = false;
    if(num_presses >= round_length) {
      if(compareChars(sequence, button_press, round_length, round_length)) {
        flash_right();
        //code to progress to the next round
        sequence[round_length] = add_character();
        round_length++;
        displaySequence(sequence, round_length);
        num_presses = 0;
        delay(250);
      } else {
        flash_wrong();
        exit(0);
      }
    }
  }
  if(incomingbyte == 6) {
    digitalWrite(LED3, LOW);
    led3_on = false;
    if(num_presses >= round_length) {
      if(compareChars(sequence, button_press, round_length, round_length)) {
        flash_right();
        //code to progress to the next round
        sequence[round_length] = add_character();
        round_length++;
        displaySequence(sequence, round_length);
        num_presses = 0;
        delay(250);
      } else {
        flash_wrong();
        exit(0);
      }
    }
  }
}
