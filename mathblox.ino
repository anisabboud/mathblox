#include "font.h";

#define DC 5
#define RST 6
#define CE 7
#define DIN 11
#define CLK 13
#define LED 9

#define BINARY_DIGITS 4
#define NUM_CHARACTERS 16
#define BOARD_LENGTH 11
#define PINS_OFFSET 10

#define ON 1
#define OFF 0

#define N 4  // How many numbers are used in each exercise.
#define NUM_SETS 15

#define EPSILON 0.0001

#define NEW_EXERCISE_BUTTON 4
boolean new_exercise_pressed = false;
#define WIN_LED 10
#define WIN_BUZZER A0

#define N 4  // How many numbers are used in each exercise.
#define NUM_SETS 15

int nums_sets[NUM_SETS][N] = {
	{1, 2, 3, 4},
	{1, 2, 3, 5},
	{1, 2, 3, 6},
	{1, 2, 4, 5},
	{1, 2, 4, 6},
	{1, 2, 5, 6},
	{1, 3, 4, 5},
	{1, 3, 4, 6},
	{1, 3, 5, 6},
	{1, 4, 5, 6},
	{2, 3, 4, 5},
	{2, 3, 4, 6},
	{2, 3, 5, 6},
	{2, 4, 5, 6},
	{3, 4, 5, 6},
};
int results[NUM_SETS][39] = {
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 21, 24, 25},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 29, 30},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 30, 31, 32, 35, 36},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 39, 40, 41, 42},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 24, 26, 27, 28, 30, 31, 32, 34, 35},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 29, 30, 32, 35, 36, 41, 42},
	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 26, 27, 28, 30, 32, 33, 40, 42, 44, 45, 47, 48},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 29, 31, 32, 33, 34, 40, 43, 44, 45, 48, 49, 50, 53, 54},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20, 21, 22, 24, 25, 26, 27, 30, 33},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 23, 24, 25, 26, 28, 29, 30, 33, 34, 40},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 29, 30, 31, 33, 34, 35, 36, 37, 39, 43, 46},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 31, 32, 33, 34, 35, 36, 38, 39, 40, 42, 48, 52},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 28, 29, 30, 31, 32, 34, 35, 36, 37, 38, 41, 44, 47, 51},
};
int results_count[NUM_SETS] = {
	20,
	22,
	26,
	29,
	33,
	39,
	30,
	32,
	34,
	39,
	27,
	31,
	38,
	39,
	39,
};

char CHARACTERS[NUM_CHARACTERS] = {' ',
                                   '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                                   '+', '-', '*', '/', '(', ')'};

char expression[BOARD_LENGTH + 1] = {0};
int binary_digits[BINARY_DIGITS];

char exercise_line1[] = "MAKE XX";
char exercise_line2[] = "WITH X,X,X,X";

int target_result = -1;
int* num_set;  // The number set array to use.

bool won = false;

// The LCD screen code is inspired by Julian Ilett:
// https://www.youtube.com/watch?v=RAlZ1DHw03g
// https://www.youtube.com/watch?v=E6PUa4n2DnA

void LcdWriteStringAt(char *characters, int x, int y) {
  LcdXY(x, y);
  while(*characters) LcdWriteCharacter(*characters++);
}

void LcdWriteStrings() {
  for(int i=0; i<504; i++) LcdWriteData(0x00); // clear LCD

  LcdWriteStringAt(exercise_line1, 20, 1);
  LcdWriteStringAt(exercise_line2, 5, 2);
  LcdWriteStringAt(expression, 10, 4);
}

void LcdWriteCharacter(char character)
{
  for(int i=0; i<5; i++) LcdWriteData(ASCII[character - 0x20][i]);
  LcdWriteData(0x00);
}

void LcdWriteData(byte dat)
{
  digitalWrite(DC, HIGH); //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, dat); //transmit serial data
  digitalWrite(CE, HIGH);
}

void LcdXY(int x, int y)
{
  LcdWriteCmd(0x80 | x);  // Column.
  LcdWriteCmd(0x40 | y);  // Row.
}

void LcdWriteCmd(byte cmd)
{
  digitalWrite(DC, LOW); //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, cmd); //transmit serial data
  digitalWrite(CE, HIGH);
}

void newExercise() {
  int num_set_index = random(NUM_SETS);
  int result_index = random(results_count[num_set_index] - 1);
  
  target_result = results[num_set_index][result_index];
  num_set = nums_sets[num_set_index];
  
  String(target_result).toCharArray(exercise_line1 + 5, 3);
  for (int i = 0; i < N; i++) {
    exercise_line2[5 + 2 * i] = '0' + num_set[i];
  }
}

void setup()
{
  delay(6000);
  Serial.begin(9600);
  
  randomSeed(analogRead(0));

  pinMode(RST, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);
  analogWrite(LED, 255);

  LcdWriteCmd(0x21);  // LCD extended commands
  LcdWriteCmd(0xBF);  // set LCD Vop (contrast)
  LcdWriteCmd(0x04);  // set temp coefficent
  LcdWriteCmd(0x14);  // LCD bias mode 1:40
  LcdWriteCmd(0x20);  // LCD basic commands
  LcdWriteCmd(0x0C);  // LCD normal video
  
  // Initialize all magnet pins to PULL_UP.
  for (int cell = 0; cell < BOARD_LENGTH; cell++) {
    int offset = (cell == 0 ? 0 : PINS_OFFSET + cell * BINARY_DIGITS);
    for (int digit = 0; digit < BINARY_DIGITS; digit++) {    
      pinMode(offset + digit, INPUT_PULLUP);
    }
  }
  
  newExercise();

  pinMode(NEW_EXERCISE_BUTTON, INPUT_PULLUP);
  
  analogWrite(LED, 255);
}

int binaryToInteger(int a[]) {
  int result = 0;
  for (int i = BINARY_DIGITS - 1; i >= 0; i--) {
    result = result * 2 + a[i];
  }
  return result;
}

void win() {
  digitalWrite(WIN_LED, 1);
  for (int i = 0; i < 6; i++) {
    analogWrite(WIN_BUZZER, 1023);
    delay(200);
    analogWrite(WIN_BUZZER, 0);
    delay(200);
  }
}

void turnLEDsOff() {
  digitalWrite(WIN_LED, 0);
  analogWrite(WIN_BUZZER, 0);
}

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

bool isOperation(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int stringLength(char* str) {
	int count = 0;
	while (*str++) count++;
	return count;
}

int countChar(char* str, char c) {
  int count = 0;
  while (*str) {
    count += *str == c;
    str++;
  }
  return count;
}

int indexOfChar(char* str, char c) {
  int index = 0;
  while (*str) {
    if (*str == c) {
      return index;
    }
    index++;
    str++;
  }
  return -1;
}

void removeChar(char* str, char c) {
  char *p = str, *q = str;
  while (*q) {
    while (*q == c) {
      q++;
    }
    *p = *q;
    p++;
    q++;
  }
  *p = 0;
}

void copyString(char* src, char* dst) {
  while(*dst++ = *src++);
}

bool isValidExpression(char* user_expression, int expected_numbers[N]) {
	// 1. Copy the user expression to a string which we can manipulate.
	char expression_copy[BOARD_LENGTH + 1];
	copyString(user_expression, expression_copy);

	// 2. Remove all spaces.
	removeChar(expression_copy, ' ');

	// 3. Locate left and right parentheses. And check that they are in valid order.
	int left_p = indexOfChar(expression_copy, '(');
	int right_p = indexOfChar(expression_copy, ')');
	if ((left_p != -1 && right_p == -1) || (left_p == -1 && right_p != -1)) {
		return false;  // Only one parenthesis appears and the other one is missing.
	}
	if (left_p != -1 && right_p != -1) {  // Both parentheses appear.
		if (left_p >= right_p) {
			return false;  // Right before left.
		}
		// There are only 4 different possible locations for each parenthesis.
		if ((left_p != 0 && left_p != 2 && left_p != 4) ||
				(right_p != 4 && right_p != 6 && right_p != 8)) {
			return false;
		}
	}

	// 4. Remove parentheses, to ease the coming validations.
	removeChar(expression_copy, '(');
	removeChar(expression_copy, ')');

	// 5. Verify that there are 3 operations and 4 numbers, in the right order.
	if (stringLength(expression_copy) != 2 * N - 1) {
		return false;
	}
	for (int i = 0; i < 2 * N - 1; i++) {
		if ((i % 2 == 0 && !isDigit(expression_copy[i])) ||
				(i % 2 == 1 && !isOperation(expression_copy[i]))) {
			return false;
		}
	}

	// 6. Check that the right set of numbers appear.
	for (int i = 0; i < N; i++) {
		if (indexOfChar(expression_copy, expected_numbers[i] + '0') == -1) {
			return false;
		}
	}

	// 7. We found nothing wrong.
	return true;
}

void loop()
{
  char expression_copy[BOARD_LENGTH + 1];
  
  // Read the user expression.
  boolean expression_changed = false;
  for (int cell = 0; cell < BOARD_LENGTH; cell++) {
    int offset = (cell == 0 ? 0 : PINS_OFFSET + cell * BINARY_DIGITS);
    for (int digit = 0; digit < BINARY_DIGITS; digit++) {
      binary_digits[digit] = !digitalRead(offset + digit);
    }
    if (expression[cell] != CHARACTERS[binaryToInteger(binary_digits)]) {
      expression[cell] = CHARACTERS[binaryToInteger(binary_digits)];
      expression_changed = true;
    }
  }
  if (expression_changed) {
    LcdWriteStrings();
  }

  // Remove Spaces from expression
  copyString(expression, expression_copy);
  removeChar(expression_copy, ' '); 

  // Check if the user expression is valid (correct numbers, and matching parentheses).
  // If it's valid, evaluate the user expression and see if it evaluates to the correct result. 
  if (isValidExpression(expression_copy, num_set) && abs(getExpressionValue(expression_copy) - target_result) < EPSILON) {
    if (!won) {
      win();
      won = true;
      LcdWriteStringAt("Great job!", 20, 1); 
      LcdWriteStringAt("Press Button", 10, 2);
    }
  } else {
    won = false;
    turnLEDsOff();
  }
  
  // Check if the "new exercise" button was pressed. If so, initialize a new game.
  boolean now_pressed = !digitalRead(NEW_EXERCISE_BUTTON);
  if (new_exercise_pressed && !now_pressed) {  // Button released.
    newExercise();
    LcdWriteStrings();
    delay(1000);
  }
  new_exercise_pressed = now_pressed;
}

//`Check validity and value of expression
// Code below inspired by http://stackoverflow.com/questions/9329406/evaluating-arithmetic-expressions-in-c
char* expressionToParse;

char peekExpr() {
    return *expressionToParse;
}

char getExpr() {
    return *expressionToParse++;
}

float expr();

float numberExpr() {
    float result = getExpr() - '0';
    while (peekExpr() >= '0' && peekExpr() <= '9')
    {
        result = 10*result + expr() - '0';
    }
    return result;
}

float factorExpr() {
    if (peekExpr() >= '0' && peekExpr() <= '9')
        return numberExpr();
    else if (peekExpr() == '(')
    {
        getExpr(); // '('
        float result = expr();
        getExpr(); // ')'
        return result;
    }
    else if (peekExpr() == '-')
    {
        getExpr();
        return -expr();
    }
    return 0; // error
}

float termExpr() {
    float result = factorExpr();
    while (peekExpr() == '*' || peekExpr() == '/')
        if (getExpr() == '*')
            result *= factorExpr();
        else
            result /= factorExpr();
    return result;
}

float expr() {
    float result = termExpr();
    while (peekExpr() == '+' || peekExpr() == '-')
        if (getExpr() == '+')
            result += termExpr();
        else
            result -= termExpr();
    return result;
}

float getExpressionValue(char* currentExpression) {
    expressionToParse = currentExpression;
    return expr();
}
