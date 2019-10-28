/* mbed TextLCD Library, for a 4-bit LCD based on HD44780
 * Copyright (c) 2007-2010, sford, http://mbed.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef MBED_TEXTLCD_H
#define MBED_TEXTLCD_H

#include "mbed.h"

//---------------------------------------------------------------------------------------------------------
// Начало изменений
//---------------------------------------------------------------------------------------------------------
/*
 *
 *
 * Changes by Bogomazyuk Vasiliy (Богомазюк Василий) 
 * Модуль испытан на жидкокристаллическом модуле MT–16S2D
 *
 *
*/


#include <string>

/*
* Настраиваем отображение курсора
* SetCursor(onCursor|onBlink); Курсор виден и мигает.
*/     
     #define onCursor           0x2 //Курсор включен
     #define offCursor          0x0 //Курсор выключен
     #define onBlink            0x1 //Курсор мигает
     #define offBlink           0x0 //Курсор не мигает
//---------------------------------------------------------------------------------------------------------
// Конец изменений
//---------------------------------------------------------------------------------------------------------


/** A TextLCD interface for driving 4-bit HD44780-based LCDs
 *
 * Currently supports 16x2, 20x2 and 20x4 panels
 *
 * @code
 * #include "mbed.h"
 * #include "TextLCD_Rus.h"
 * #include <string>
 * 
 * TextLCD lcd(D12, D11, D5, D4, D3, D2); // rs, e, d4, d5, d6, d7
 * 
 * 
 * //---------------------------------------------------------------------------------------------------------
 * // Обратите внимание, что русские символы передаются в двухбайтовом представлении (UTF-16)
 * //---------------------------------------------------------------------------------------------------------
 * const uint16_t ABC[66]={'А','Б','В','Г','Д','Е','Ё','Ж','З','И','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь','Э','Ю','Я',
 *                    'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я'};
 * string str="пример::  AABBCCDDeeffgghh";
 * 
 * int pattern[8][8]={{0xA,0x15,0x0,0x10,0x8,0x4,0x2,0x1},{0x15,0xA,0x0,0x4,0x4,0x4,0x4,0x4},{0xA,0x15,0x0,0x1,0x2,0x4,0x8,0x10},{0x15,0xA,0x0,0x0,0x0,0x1F,0x0,0x0},
 *                    {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},{0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18},{0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C},{0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E}};
 * 
 * int main() {
 * 
 * //---------------------------------------------------------------------------------------------------------
 * // Вывод на экран текста без "руссификации", т.е. как есть
 * //---------------------------------------------------------------------------------------------------------
 *       lcd.cls();
 *       lcd.printf("The module");
 *       lcd.locate(0,1);
 *       lcd.printf("TextLCD_Rus");
 *       wait(3);
 * //---------------------------------------------------------------------------------------------------------
 * // Вывод на экран русского текста
 * //---------------------------------------------------------------------------------------------------------
 *       lcd.cls();
 *       lcd.print_rus("Вывод  текста  на  русском  языке!!");
 *       wait(3);
 *       lcd.cls();
 * 
 *       lcd.print_rus("Посимвольно::");
 *       wait(3);
 *       lcd.cls();
 *       for (int i=0; i<33; i++) {
 *           lcd.locate(0,0);
 *           lcd.putc_rus(ABC[i]);
 *           lcd.locate(0,1);
 *           lcd.putc_rus(ABC[i+33]);
 *           wait(0.5);
 *         };
 * //---------------------------------------------------------------------------------------------------------
 * // Для вывода теста, содержащего как русские, так и остальные символы необходимо любые другие символы удваивать
 * // Обратите внимание, что параметром функции print_rus является экземпляр объекта string
 * //---------------------------------------------------------------------------------------------------------
 *       lcd.cls();
 *       lcd.print_rus("Вывод  смешенной  строки::");
 *       wait(3);
 *       lcd.cls();
 *       lcd.print_rus("Рассмотрим");
 *       lcd.locate(0,1);
 *       lcd.print_rus(str);
 *       wait(3);
 *       lcd.cls();
 * //---------------------------------------------------------------------------------------------------------
 * // Применение функции сдвига экрана, обратите внимание, что строка "Влево..." вводится за пределами видимой области
 * //---------------------------------------------------------------------------------------------------------
 *       lcd.print_rus("Двигаем  текст......");
 *       lcd.locate(0,1);
 *       lcd.print_rus("Вправо......");
 *       wait(0.5);
 *       for (int i=0; i<16;i++) {
 *         lcd.ShiftLCD_Right();
 *         wait(0.5);
 *       };
 *       lcd.locate(0,1);
 *       lcd.print_rus("Влево......  ");
 *       for (int i=0; i<32;i++) {
 *         lcd.ShiftLCD_Left();
 *         wait(0.5);
 *       };
 * //---------------------------------------------------------------------------------------------------------
 * // Управление видимостью курсора
 * //---------------------------------------------------------------------------------------------------------
 *       lcd.cls();
 *       lcd.print_rus("Курсор  невиден");
 *       wait(5);
 *       lcd.locate(0,1);
 *       lcd.print_rus("Он  вверху  слева  ");
 *       lcd.CursorPosition(0,0);
 *       wait(5);
 *       lcd.locate(0,1);
 *       lcd.print_rus("Символ  мигает      ");
 *       lcd.CursorPosition(0,0);
 *       lcd.SetCursor(offCursor|onBlink);
 *       wait(5);
 *       lcd.cls();
 *       lcd.print_rus("Курсор  виден");
 *       lcd.CursorPosition(0,0);
 *       lcd.SetCursor(onCursor|offBlink);
 *       lcd.locate(0,1);
 *       lcd.print_rus("Он  вверху  слева  ");
 *       lcd.CursorPosition(0,0);
 *       wait(5);
 *       lcd.locate(0,1);
 *       lcd.print_rus("И  он  не  мигает    ");
 *       lcd.CursorPosition(0,0);
 *       lcd.SetCursor(onCursor|offBlink);
 *       wait(5);
 *       lcd.locate(0,1);
 *       lcd.print_rus("А  теперь  мигает  ");
 *       lcd.CursorPosition(0,0);
 *       lcd.SetCursor(onCursor|onBlink);
 *       wait(5);
 * //---------------------------------------------------------------------------------------------------------
 * // Включение/выключение дисплея
 * //---------------------------------------------------------------------------------------------------------
 *       lcd.cls();
 *       lcd.print_rus("Выключим  дисплей");
 *       wait(3);
 *       lcd.off();
 *       wait(3);
 *       lcd.on();
 *       lcd.locate(0,0);
 *       lcd.print_rus("Включили  дисплей");
 *       wait(3);
 *       lcd.cls();
 * //---------------------------------------------------------------------------------------------------------
 * // Пример управления позиционированием курсора
 * //---------------------------------------------------------------------------------------------------------
 *       lcd.print_rus("Двигаем  курсор");
 *       lcd.locate(0,1);
 *       for (int i=0; i<16; i++) lcd.putc(0x13);
 *       lcd.CursorPosition(0,1);
 *       wait(0.5);
 *       lcd.SetCursor(offCursor|onBlink);
 *       for (int i=0; i<16; i++) {
 *           lcd.ShiftCursor_Right();
 *           wait(0.5);
 *         };
 *       lcd.locate(0,1);
 *       for (int i=0; i<16; i++) lcd.putc(0x14);
 *       wait(0.5);
 *       for (int i=0; i<16; i++) {
 *           lcd.ShiftCursor_Left();
 *           wait(0.5);
 *         };
 *       lcd.locate(0,1);
 *       lcd.print_rus("Сдвинем  в  1155,,00    ");
 *       lcd.CursorPosition(15,0);
 *       wait(3);
 *       lcd.locate(0,1);
 *       lcd.print_rus("В  начало  строки  ");
 *       lcd.home();
 *       wait(3);
 * //---------------------------------------------------------------------------------------------------------
 * // Использование пользовательских символов
 * //---------------------------------------------------------------------------------------------------------
 *      lcd.SetCursor(offCursor|offBlink);
 *      lcd.cls();
 *      lcd.print_rus("Программируемые  символы");
 *      for (int i=0; i<8; i++) lcd.writeCGRAM(i, pattern[i]);
 *      wait(3);
 *      lcd.cls();
 *      wait(0.5);
 *      int loc=0;
 *      for (int i=0; i<16; i++) {
 *          for (int k=4; k<9; k++) {
 *              lcd.locate(0,0);
 *              for (int j=0; j<16; j++) lcd.putc((k+j) % 4);
 *              lcd.locate(loc,1);
 *              if (k<8) {lcd.putc(k);} else lcd.putc(0xFF);
 *              wait(0.2);
 *             };
 *          loc++;
 *         };
 *      wait(2);     
 * }
 * @endcode
 */
 
class TextLCD : public Stream {
public:

    /** LCD panel format */
    enum LCDType {
        LCD16x2     /**< 16x2 LCD panel (default) */
        , LCD16x2B  /**< 16x2 LCD panel alternate addressing */
        , LCD20x2   /**< 20x2 LCD panel */
        , LCD20x4   /**< 20x4 LCD panel */
        , LCD24x2   /**< 24x2 LCD panel */
        , LCDuser   /** User defined LCD, rows/columns must be set */
    };

    /** Create a TextLCD interface
     *
     * @param rs    Instruction/data control line
     * @param e     Enable line (clock)
     * @param d4-d7 Data lines
     * @param type  Sets the panel size/addressing mode (default = LCD16x2)
     */
    TextLCD(PinName rs, PinName e, PinName d4, PinName d5, PinName d6, PinName d7, LCDType type = LCD16x2);

 #if DOXYGEN_ONLY
    /** Write a character to the LCD
     *
     * @param c The character to write to the display
     */
    int putc(int c);

    /** Write a formated string to the LCD
     *
     * @param format A printf-style format string, followed by the
     *               variables to use in formating the string.
     */
     
     
    int printf(const char* format, ...);
 #endif

    /** Locate to a screen column and row
     *
     * @param column  The horizontal position from the left, indexed from 0
     * @param row     The vertical position from the top, indexed from 0
     */
    void locate(int column, int row);
    /** Clear the screen and locate to 0,0 */
    void cls();
    
    struct LCDparam {
      int rows;           // number of lines //
      int columns;        // number of columns //
      int delay;          // delay for commands microseconds //
      int adresses[4];    // start adresses for 4 lines //
    } LCDparam;
    
    /** write a user defined char
     *
     * @param address  The user defined char (0-7)
     * @param pattern[8] bit pattern 5*8 of char
     */ 
    void writeCGRAM(int address, int pattern[8]);
    
    /** Get the char at the current position
     * 
     * int getc() 
     */
     void writeCommand(int command);
     
     
//---------------------------------------------------------------------------------------------------------     
// Дополнительные команды, в оригинальном модуле их нет
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
// Начало изменений
//---------------------------------------------------------------------------------------------------------
     /** Выводим в позиции курсора символ русского языка */
     int putc_rus(int c);
     /** 
      *  Выводит строку начиная с позиции курсора строку содержащюю русские символы. Для вывода остальных символов их необходимо удвоить.
      *  Например строка "Привет!!  Как дела??" на экране будет выведена как "Привет! Как дела?"
     */
     void print_rus(const string rustext);

     /** Сдвиг текста влево */
     void ShiftLCD_Left();
     /** Сдвиг текста вправо */
     void ShiftLCD_Right();
     
 
     /**
     * Настраиваем отображение курсора
     @param modeCursor Задает режим отображения курсора. Пример: SetCursor(onCursor|onBlink); Курсор виден и мигает.
     @param "#define onCursor           0x2"  Курсор включен
     @param "#define offCursor          0x0"  Курсор выключен
     @param "#define onBlink            0x1"  Курсор мигает
     @param "#define offBlink           0x0"  Курсор не мигает
     */
     void SetCursor(int modeCursor);
     /** Сдвиг курсора влево */
     void ShiftCursor_Left();
     /** Сдвиг курсора вправо */
     void ShiftCursor_Right();
     /** Устанавливаем курсор в позицию column, row */
     void CursorPosition(int column, int row);
     /** Помещает курсор в левую позицию (начало строки) */
     void home();
     
     /** Включает дисплей */
     void on();
     /** Выключает дисплей */
     void off();
     
//---------------------------------------------------------------------------------------------------------
// Конец изменений
//---------------------------------------------------------------------------------------------------------   
   
protected:

    // Stream implementation functions
    virtual int _putc(int value);
    virtual int _getc();

    int address(int column, int row);
    void character(int column, int row, int c);
    void writeByte(int value);
    void writeData(int data);
    void setLCDparam(LCDType _type);
    DigitalOut _rs, _e;
    BusOut _d;
    LCDType _type;

    int _column;
    int _row;
//---------------------------------------------------------------------------------------------------------
// Начало изменений
//---------------------------------------------------------------------------------------------------------
    int _setCursor; // Храним текущие настройки вида курсора
//---------------------------------------------------------------------------------------------------------
// Конец изменений
//---------------------------------------------------------------------------------------------------------
};

#endif
