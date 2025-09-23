
**9/23/2025**
*  **feedback.md is for instructor use only. DO NOT change the feedback.md**; make a copy if needed
* I will replace this lab’s score with your next lab score, as long as the next lab score is higher and all mistakes from this lab are corrected
* class definition style & standards:  first, member vars  none per line and do not forget to initialize them;  second functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back and list all getters back to back; start with a default c’tor, followed by  copy c’tor (if any), then other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions should be const; all functions with more than one statement should be normal (defined externally, outside of the class and below main()), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition; all member variables must be private; classes must provide a strong exception guarantee; must have default c’tor; implement Rule of Three when necessary
* To provide you with thorough feedback, your instructor reads your code line by line, sometimes multiple times. Jumping from file to file is too time-consuming. Unless noted otherwise, place your class definitions above the main()  and all function definitions below main(), all in one file. While the industry standard involves multi-source file programs, we will use a single file format for these labs unless instructed otherwise.
* Posted instructions are not optional, and not following the instructions will result in a lower grade. It applies to all assignments in this course.
* 143 and like: what if numbers/limits/lengths change? Will you remember to update them everywhere where they are being used? What are the chances that you or whoever maintains the code forgets to change it in one or more places?  Do not hard-code numeric values other than 1 and zero; If it is not 1 or 0, make it const, e.g., tempt, in case of ASCII values, use chars, e.g., temp>’a’ -5
* 226 what if a file has more records than the array can fit?  Does not check for array boundary -5
* 115 – allows an object to become invalid -5
* 233-311  poor logic; SetAccount should be responsible for calling and set member variables only all incoming values and their combination are valid
* should create member functions that call the validators function for each member of the class -2 
* moving forward, using exit (), will result in a grade of zero -5
* 146 and like why set it to invalid to begin with? -2
* 203 – should return a string formatted in columns, not single blank spaces -2
* 403-417 – how does it make it good test data? -2
* data should be displayed in a table format with column headings whenever possible; text entries should be left aligned; and numerical entries should be right aligned with the same number of decimal places: $$ amount should have 2 or 4 decimal places -2
* 40 and like: to promote string exception guarantee, all variables, including members of struct and classes, should be initialized to appropriate default values at the time of definition/declaration; each var/obj should be defined on separate lines -2
* poor Id(s)  and/or inconsistent naming convention; ids should be self-documenting and as short as possible; use verbs for functions and nouns for variables; use camel-casing for variables (errorMessage) enum & const should be in upper case with words separated by “_”, e.g., MAX_TERMS, PRINT_RECORDS; pointer variables should start with p( if single)  or pp( if double pointer); flags isValid ( clearly what true would mean); if copying – e.g rhsQueue or scrQueue ; do not use IDs that are same as or very similar to C++  keywords and functions; no need to call an array “array”- it is obvious; vars should not be called value; -2
```text
void validateInput(BankAccount validList[], BankAccount invalidList[], int &validSize, int &invalidSize)   // it looks like  the purpose of this function is to create new accounts, validation is implied

```
* 44 should be a member function -2
* default member variable values should be const -2
* why waste time and space to store invalid accounts?  -2
* 80-82 should create a highly reusable function that takes an error message string as a parameter and clears the failed input; it does not need to ask the user to re-enter, the menu loop already does it  -2
* 128 – what for?  -2
* hard to read menu in the code; it should look similar to it appearance on a screen -1
```text
//e.g.
cout << "\n\nMenu:\n”
“1. Encrypt\n”
“2. Decrypt\n”
“3. Quit\n"<<endl;
```
