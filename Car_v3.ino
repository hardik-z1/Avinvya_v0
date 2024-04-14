const int a1 = 7; //ackw m1
const int a2 = 5; //ackw m2
const int c1 = 6; //ckw m1
const int c2 = 4; //ckw m2

//pwm is sent to these pins:
const int e1 = 11; //enable motor1
const int e2 = 10; //enable motor2

void setup() {
  // put your setup code here, to run once:
  //Setting up pins:
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(c1, LOW);
  digitalWrite(c2, LOW);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {

    //Taking Input
    String btIn = Serial.readString();
    Serial.println(btIn);
    String fbd = btIn.substring(0, 3);
    String lrd = btIn.substring(3, 6);
    int fb = fbd.toInt();
    int lr = lrd.toInt();
    fb = map(fb, 0, 255, 0, 510);
    lr = map(lr, 0, 255, 0, 510);
    Serial.print(fb);
    Serial.print(" | ");
    Serial.print(lr);
    Serial.print(" | ");
  

  //Setting fwd/bkd of wheels and making fwd)0-255)
  if(fb>=256){
    fb = fb-255;
    digitalWrite(c1, HIGH);
    digitalWrite(c2, HIGH);
    digitalWrite(a1, LOW);
    digitalWrite(a2, LOW);
  }
  else{
    fb = 255-fb;
    digitalWrite(a1, HIGH);
    digitalWrite(a2, HIGH);
    digitalWrite(c1, LOW);
    digitalWrite(c2, LOW);
  }
  
  //Setting speed based on left/right:
  int m1 = fb;
  int m2 = fb;
  if(lr>=256){
    lr = lr-255;
    m1 = m1-lr;
    m2 = m2+lr;
  }
  else{
    lr = 255-lr;
    m1 = m1+lr;
    m2 = m2-lr;
  }

  //Setting Boundary conditions:
  //if(m1>=255) m1 = 255;
  //if(m2>=255) m2 = 255;
  if(m1<=0) m1 = 0;
  if(m2<=0) m2 = 0;
  if(m1>=180) m1 = 180;
  if(m2>=180) m2 = 180;

  //Printing pwms sent:
  Serial.print(m1);
  Serial.print(" | ");
  Serial.println(m2);

  //Sending signal to the motors:
  analogWrite(e1, m1);
  analogWrite(e2, m2);
  delay(1);
  }
}
