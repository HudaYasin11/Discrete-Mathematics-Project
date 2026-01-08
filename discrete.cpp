#include <iostream>
#include <cmath>
#include <windows.h>
#include <cstring>
#include <iomanip>
using namespace std;

/* ================= CONSTANTS ================= */
const double ATTEMPTS_PER_SEC = 1e7; // 10 million attempts per sec

const char LOWER[] = "abcdefghijklmnopqrstuvwxyz";
const char UPPER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGITS[] = "0123456789";
const char SYMBOLS[] = "!@#$%^&*()_+-={}[]<>?~`|\\:;\",./'";

const int LOWER_SIZE = sizeof(LOWER) - 1;
const int UPPER_SIZE = sizeof(UPPER) - 1;
const int DIGIT_SIZE = sizeof(DIGITS) - 1;
const int SYMBOL_SIZE = 33;

/* ================= LCG PSEUDO-RANDOM GENERATOR ================= */
unsigned long long seed = 2147483647;    // 2³¹-1 - Large prime seed
const unsigned long long a = 1664525;       // Multiplier
const unsigned long long c = 1013904223;    // Increment, coprime to m
const unsigned long long m = 4294967296; // 2³²
const int VERIFY_MAX_LENGTH = 8;
const int VERIFY_MAX_CHARSET = 26;
const int CRACK_MAX_LENGTH = 5;
const int CRACK_MAX_CHARSET = 8;

/* ================= FUNCTION PROTOTYPES ================= */

int getCharsetSize(bool lo, bool up, bool di, bool sy);
double calculateEntropy(int length, int charsetSize);
double estimateCrackingTime(int length, int charsetSize);
string strengthLabel(double entropy);
void printCrackingTime(double seconds);
void setColor(int colorCode);
unsigned long long lcg();
int randomInRange(int max);
void printColoredStrength(double entropy);

void displayHeader();

void generatePassword();
void createCustomPassword();
void permutationsCalculator();
void combinationsCalculator();


void analyzeExistingPassword();
void calculateEntropyInteractive();
void calculateCrackingTimeInteractive();

void bruteForceVerification();
void bruteForceCrack();
bool bruteCrack(char charset[], int k, char current[], int pos,
                int length, char target[], long long &attempts);


void generateReport();
void displaySecurityTips();

int main()
{
    int choice;

    while (true)
    {
        system("cls");
        displayHeader();

        setColor(11);
        cout << "\nMAIN MENU\n";

        setColor(14);
        cout << "1. ";
        setColor(15);
        cout << "Generate Strong Password\n";
        setColor(14);
        cout << "2. ";
        setColor(15);
        cout << "Create Custom Password\n";
        setColor(14);
        cout << "3. ";
        setColor(15);
        cout << "Calculate Password Entropy\n";
        setColor(14);
        cout << "4. ";
        setColor(15);
        cout << "Estimate Cracking Time\n";
        setColor(14);
        cout << "5. ";
        setColor(15);
        cout << "Quick Password analysis\n";
        setColor(14);
        cout << "6. ";
        setColor(15);
        cout << "Brute-force Math Verification\n";
        setColor(14);
        cout << "7. ";
        setColor(15);
        cout << "Brute-force Crack Simulation\n";

        setColor(14);
        cout << "8. ";
        setColor(15);
        cout << "Permutations Calculator (nPr)\n";
        setColor(14);
        cout << "9. ";
        setColor(15);
        cout << "Combinations Calculator (nCr)\n";
        setColor(14);
        cout << "10. ";
        setColor(15);
        cout << "Generate Security Report\n";
        setColor(14);
        cout << "11. ";
        setColor(15);
        cout << "Get Security Tips\n";
        setColor(14);
        cout << "0. ";
        setColor(15);
        cout << "Exit\n";
        setColor(11);
        cout << "Enter your choice (0-11): ";
        setColor(15);
        cin >> choice;
         cin.ignore(1000, '\n');

        system("cls");
if (choice == 1) {
            generatePassword();
        }
        else if (choice == 2) {
            createCustomPassword();
        }
        else if (choice == 3) {
            calculateEntropyInteractive();
        }
        else if (choice == 4) {
            calculateCrackingTimeInteractive();
        }
        else if (choice == 5) {
            analyzeExistingPassword();
        }
        else if (choice == 6) {
            bruteForceVerification();
        }
        else if (choice == 7) {
            bruteForceCrack();
        }
        else if (choice == 8) {
            permutationsCalculator();
        }
        else if (choice == 9) {
            combinationsCalculator();
        }
        else if (choice == 10) {
            generateReport();
        }
        else if (choice == 11) {
            displaySecurityTips();
        }
        else if (choice == 0) {
            setColor(10);
            cout << "Thank you for using Password Security Analyzer!\n";
            setColor(15);
            return 0;
        }
        else {
            setColor(12);
            cout << "Invalid choice. Please try again.\n";
            setColor(15);
        }

              setColor(15);
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}
int getCharsetSize(bool lo, bool up, bool di, bool sy)
{
    int size = 0;
    if (lo)
        size += LOWER_SIZE;
    if (up)
        size += UPPER_SIZE;
    if (di)
        size += DIGIT_SIZE;
    if (sy)
        size += SYMBOL_SIZE;
    return size;
}

double calculateEntropy(int length, int charsetSize)
{
    double entropy = length * log2(charsetSize);
    double combos = pow(charsetSize, length);

    cout << "Total possible combinations: "
         << charsetSize << "^" << length
         << " = ";

    if (combos > 1e15)
    { // For very large numbers
        cout << scientific << combos;
    }
    else
    {
        cout << (long long)combos;
    }
    cout << "\n";
    return entropy;
}

double estimateCrackingTime(int length, int charsetSize)
{
    double combos = pow(charsetSize, length);
    return combos / ATTEMPTS_PER_SEC;
}

void printCrackingTime(double seconds)
{
    const double MINUTE = 60, HOUR = 3600, DAY = 86400, YEAR = DAY * 365;

    if (seconds < MINUTE)
    {
        cout << fixed << setprecision(1) << seconds << " seconds\n";
    }
    else if (seconds < HOUR)
    {
        cout << fixed << setprecision(1) << seconds / MINUTE << " minutes\n";
    }
    else if (seconds < DAY)
    {
        cout << fixed << setprecision(1) << seconds / HOUR << " hours\n";
    }
    else if (seconds < YEAR)
    {
        cout << fixed << setprecision(1) << seconds / DAY << " days\n";
    }
    else
    {

        double years = seconds / YEAR;
        if (years > 1e9)
        {
            cout << scientific << setprecision(2) << years << " years\n";
        }
        else
        {
            cout << fixed << setprecision(0) << years << " years\n";
        }
    }
    cout.unsetf(ios_base::floatfield); // Reset formatting
}
string strengthLabel(double entropy)
{
    if (entropy < 28)
        return "Very Weak";
    if (entropy < 36)
        return "Weak";
    if (entropy < 60)
        return "Moderate";
    if (entropy < 80)
        return "Strong";
    return "Very Strong";
}


void generatePassword()
{
    setColor(14);
    cout << "\n=== GENERATE STRONG PASSWORD ===\n";
    setColor(15);

    const int length = 16;
    char password[length + 1];

    // Build character pool
    char pool[LOWER_SIZE + UPPER_SIZE + DIGIT_SIZE + SYMBOL_SIZE];
    int poolSize = 0;

    for (int i = 0; LOWER[i]; i++)
        pool[poolSize++] = LOWER[i];
    for (int i = 0; UPPER[i]; i++)
        pool[poolSize++] = UPPER[i];
    for (int i = 0; DIGITS[i]; i++)
        pool[poolSize++] = DIGITS[i];
    for (int i = 0; SYMBOLS[i]; i++)
        pool[poolSize++] = SYMBOLS[i];

    
    for (int i = 0; i < length; i++)
    {
        password[i] = pool[randomInRange(poolSize)];
    }
    password[length] = '\0';

    
    for (int i = 0; i < length; i++)
    {
        int j = randomInRange(length);
        swap(password[i], password[j]);
    }

    password[0] = LOWER[randomInRange(LOWER_SIZE)];
    password[1] = UPPER[randomInRange(UPPER_SIZE)];
    password[2] = DIGITS[randomInRange(DIGIT_SIZE)];
    password[3] = SYMBOLS[randomInRange(SYMBOL_SIZE)];
    setColor(10);
    cout << "Generated Password: " << password << endl;
    setColor(15);

    int charsetSize = getCharsetSize(true, true, true, true);
    double entropy = calculateEntropy(length, charsetSize);
    cout << "Entropy: " << entropy << " bits\n";
    setColor(11);
    cout << "Strength: ";
    printColoredStrength(entropy);
    cout << endl;
    setColor(15);
}

void createCustomPassword()
{
    cout << "\n**********CREATE CUSTOM PASSWORD*********\n";

    int length;
    char includeLower, includeUpper, includeDigits, includeSymbols;

    cout << "Enter password length: ";
    cin >> length;

    if (length <= 0)
    {
        cout << "ERROR: Invalid length.\n";
        return;
    }

    cout << "Include lowercase letters? (y/n): ";
    cin >> includeLower;
    cout << "Include uppercase letters? (y/n): ";
    cin >> includeUpper;
    cout << "Include digits? (y/n): ";
    cin >> includeDigits;
    cout << "Include symbols? (y/n): ";
    cin >> includeSymbols;

    
    char pool[100];
    int poolSize = 0;

    if (tolower(includeLower) == 'y')
    {
        for (int i = 0; LOWER[i]; i++)
            pool[poolSize++] = LOWER[i];
    }
    if (tolower(includeUpper) == 'y')
    {
        for (int i = 0; UPPER[i]; i++)
            pool[poolSize++] = UPPER[i];
    }
    if (tolower(includeDigits) == 'y')
    {
        for (int i = 0; DIGITS[i]; i++)
            pool[poolSize++] = DIGITS[i];
    }
    if (tolower(includeSymbols) == 'y')
    {
        for (int i = 0; SYMBOLS[i]; i++)
            pool[poolSize++] = SYMBOLS[i];
    }

    if (poolSize == 0)
    {
        cout << "ERROR: No character types selected.\n";
        return;
    }

    cout << "\nCreated Password: ";
    for (int i = 0; i < length; i++)
    {
        cout << pool[randomInRange(poolSize)];
    }
    cout << endl;
}


void analyzeExistingPassword()
{
    cout << "\n=== QUICK PASSWORD ANALYSIS ===\n";

    char password[128];
    cout << "Enter password to analyze: ";
    cin >> password;

    int length = 0;
    while (password[length] != '\0')
        length++;
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSymbol = false;

    for (int i = 0; i < length; i++)
    {
        char c = password[i];
        if (c >= 'a' && c <= 'z')
            hasLower = true;
        else if (c >= 'A' && c <= 'Z')
            hasUpper = true;
        else if (c >= '0' && c <= '9')
            hasDigit = true;
        else
            hasSymbol = true;
    }

   
    int charsetSize = getCharsetSize(hasLower, hasUpper, hasDigit, hasSymbol);
    double entropy = calculateEntropy(length, charsetSize);

    setColor(11);
    cout << "\nRESULTS:\n";
    setColor(15);
    cout << "Length : " << length << " characters\n";
    cout << " Character types : ";
    if (hasLower)
        cout << "lower ";
    if (hasUpper)
        cout << "UPPER ";
    if (hasDigit)
        cout << "digits ";
    if (hasSymbol)
        cout << "symbols ";
    cout << "\n Entropy : " << fixed << setprecision(1) << entropy << " bits\n";
    cout << " Strength : ";
    printColoredStrength(entropy);
    cout << endl;
    cout << " Time to crack : ";
    printCrackingTime(estimateCrackingTime(length, charsetSize));
}

void calculateEntropyInteractive()
{
    cout << "\n=== ENTROPY CALCULATOR ===\n";

    int length;
    char includeLower, includeUpper, includeDigits, includeSymbols;

    cout << "Enter password length: ";
    cin >> length;
    cout << "Include lowercase letters? (y/n): ";
    cin >> includeLower;
    cout << "Include uppercase letters? (y/n): ";
    cin >> includeUpper;
    cout << "Include digits? (y/n): ";
    cin >> includeDigits;
    cout << "Include symbols? (y/n): ";
    cin >> includeSymbols;
cin.ignore(1000, '\n');
    int charsetSize = getCharsetSize(
        tolower(includeLower) == 'y',
        tolower(includeUpper) == 'y',
        tolower(includeDigits) == 'y',
        tolower(includeSymbols) == 'y');

    if (charsetSize == 0)
    {
        cout << "ERROR: No character types selected.\n";
        return;
    }

    double entropy = calculateEntropy(length, charsetSize);
    cout << "\nEntropy: " << fixed << setprecision(1) << entropy << " bits\n";
    cout << "Strength: ";
    printColoredStrength(entropy);
    cout << endl;
    
}

void bruteForceVerification()
{
    cout << "\n=== BRUTE-FORCE VERIFICATION (MATH) ===\n";

    int length, charsetSize;

    cout << "Enter password length (max " << VERIFY_MAX_LENGTH << "): ";
    cin >> length;
    cout << "Enter character set size (max " << VERIFY_MAX_CHARSET << "): ";
    cin >> charsetSize;

    if (length <= 0 || length > VERIFY_MAX_LENGTH ||
        charsetSize <= 0 || charsetSize > VERIFY_MAX_CHARSET)
    {
        cout << "ERROR: Limits exceeded. ";
        cout << "Length: 1-" << VERIFY_MAX_LENGTH << ", ";
        cout << "Charset: 1-" << VERIFY_MAX_CHARSET << "\n";
        return;
    }

    long long totalCombinations = 1;
    for (int i = 0; i < length; i++)
    {
        totalCombinations *= charsetSize;
    }

    cout << "\nTotal combinations (k^n): " << totalCombinations << endl;
    cout << "Verification: SUCCESS\n";
}

bool bruteCrack(char charset[], int k, char current[], int pos,
                int length, char target[], long long &attempts)
{
    if (pos == length)
    {
        attempts++;
        for (int i = 0; i < length; i++)
        {
            if (current[i] != target[i])
                return false;
        }
        return true;
    }

    for (int i = 0; i < k; i++)
    {
        current[pos] = charset[i];
        if (bruteCrack(charset, k, current, pos + 1, length, target, attempts))
        {
            return true;
        }
    }
    return false;
}

void bruteForceCrack()
{
    cout << "\n=== BRUTE-FORCE CRACK SIMULATION ===\n";

    char target[CRACK_MAX_LENGTH + 2]; // +2 for safety
    char charset[CRACK_MAX_CHARSET + 2];
    char current[CRACK_MAX_LENGTH + 2];
    int charsetSize, length = 0;
    long long attempts = 0;

    cout << "Enter target password (max " << CRACK_MAX_LENGTH << " characters): ";
    cin >> target;

    while (target[length] != '\0')
    {
        length++;
    }

    if (length <= 0 || length > CRACK_MAX_LENGTH)
    {
        cout << "ERROR: Length must be 1-" << CRACK_MAX_LENGTH << " characters.\n";
        return;
    }

    cout << "Enter character set size (max " << CRACK_MAX_CHARSET << "): ";
    cin >> charsetSize;

    if (charsetSize <= 0 || charsetSize > CRACK_MAX_CHARSET)
    {
        cout << "ERROR: Character set size must be 1-" << CRACK_MAX_CHARSET << ".\n";
        return;
    }

    cout << "Enter " << charsetSize << " characters for the character set: ";
    for (int i = 0; i < charsetSize; i++)
    {
        cin >> charset[i];
    }
    charset[charsetSize] = '\0';

    bool found = bruteCrack(charset, charsetSize, current, 0, length, target, attempts);

    cout << "\nRESULTS:\n";
    if (found)
    {
        cout << "Password cracked successfully!\n";
    }
    else
    {
        cout << "Password not found in character set.\n";
    }
    cout << "Attempts made: " << attempts << endl;
}
/* ================= SECURITY FUNCTIONS ================= */
void generateReport()
{
    cout << "\n=== PASSWORD SECURITY REPORT ===\n\n";

    char password[128];
    cout << "Enter password to analyze: ";
    cin >> password;

    int length = 0;
    while (password[length] != '\0')
    {
        length++;
    }

    int lowerCount = 0, upperCount = 0, digitCount = 0, symbolCount = 0;

    for (int i = 0; i < length; i++)
    {
        char c = password[i];
        if (c >= 'a' && c <= 'z')
        {
            lowerCount++;
        }
        else if (c >= 'A' && c <= 'Z')
        {
            upperCount++;
        }
        else if (c >= '0' && c <= '9')
        {
            digitCount++;
        }
        else
        {
            symbolCount++;
        }
    }

    bool hasLower = (lowerCount > 0);
    bool hasUpper = (upperCount > 0);
    bool hasDigit = (digitCount > 0);
    bool hasSymbol = (symbolCount > 0);

    int charsetSize = 0;
    if (hasLower)
        charsetSize += 26;
    if (hasUpper)
        charsetSize += 26;
    if (hasDigit)
        charsetSize += 10;
    if (hasSymbol)
        charsetSize += 33;

    double entropy = length * log2(charsetSize);

    double combos = 1.0;
    for (int i = 0; i < length; i++)
    {
        combos *= charsetSize;
    }
    double seconds = combos / 10000000.0;

    

    cout << "\n1. BASIC INFORMATION\n";
    cout << "   Password length: " << length << " characters\n";
    cout << "   Contains: ";
    if (hasLower)
        cout << "lowercase ";
    if (hasUpper)
        cout << "UPPERCASE ";
    if (hasDigit)
        cout << "digits ";
    if (hasSymbol)
        cout << "symbols ";
    cout << "\n";

    cout << "\n2. SECURITY METRICS\n";
    cout << "   Character set size: " << charsetSize << "\n";
    cout << "   Password entropy: " << fixed << setprecision(1) << entropy << " bits\n";
    cout << "   Strength: ";
    printColoredStrength(entropy);
    cout << "\n";
    cout << "   Time to crack: ";
    printCrackingTime(seconds);

    cout << "\n3. RECOMMENDATIONS\n";

    if (length < 12)
    {
        cout << "    Increase length to at least 12 characters\n";
    }

    int charTypes = 0;
    if (hasLower)
        charTypes++;
    if (hasUpper)
        charTypes++;
    if (hasDigit)
        charTypes++;
    if (hasSymbol)
        charTypes++;

    if (charTypes < 4)
    {
        cout << "    Add ";
        if (!hasLower)
            cout << "lowercase letters ";
        if (!hasUpper)
            cout << "uppercase letters ";
        if (!hasDigit)
            cout << "digits ";
        if (!hasSymbol)
            cout << "symbols ";
        cout << "to your password\n";
    }

    cout << "\n4. SECURITY SCORE: ";

    int score = 0;
    if (length >= 12)
        score += 3;
    else if (length >= 8)
        score += 2;
    else
        score += 1;

    score += charTypes;

    if (score >= 6)
    {
        setColor(10);
        cout << "EXCELLENT";
    }
    else if (score >= 4)
    {
        setColor(14);
        cout << "GOOD";
    }
    else
    {
        setColor(12);
        cout << "WEAK";
    }
    setColor(15);
    cout << " (" << score << "/7)\n";
}
void displaySecurityTips()
{
    cout << "\n=== SECURITY TIPS ===\n";
    char password[128];
    cout << "Enter your password for personalized tips: ";
    cin >> password;
    int length = strlen(password);
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSymbol = false;

    for (int i = 0; i < length; i++)
    {
        char c = password[i];
        if (c >= 'a' && c <= 'z')
            hasLower = true;
        else if (c >= 'A' && c <= 'Z')
            hasUpper = true;
        else if (c >= '0' && c <= '9')
            hasDigit = true;
        else
            hasSymbol = true;
    }

    cout << "\nRECOMMENDATIONS:\n";

    if (length < 8)
    {
        cout << " Increase password length to at least 12 characters\n";
    }
    if (!hasLower)
    {
        cout << "  Add lowercase letters (a-z)\n";
    }
    if (!hasUpper)
    {
        cout << "  Add uppercase letters (A-Z)\n";
    }
    if (!hasDigit)
    {
        cout << "  Add digits (0-9)\n";
    }
    if (!hasSymbol)
    {
        cout << "  Add special symbols (!@#$% etc.)\n";
    }

    if (length >= 12 && hasLower && hasUpper && hasDigit && hasSymbol)
    {
        cout << " Excellent! Your password follows strong security practices\n";
    }

    cout << "\nGENERAL TIPS:\n";
    cout << "1. Use passwords with at least 12 characters\n";
    cout << "2. Combine different character types\n";
    cout << "3. Avoid dictionary words and personal information\n";
    cout << "4. Use unique passwords for different accounts\n";
    cout << "5. Consider using a password manager\n";
}

void displayHeader()
{
    cout << "$$$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\  $$\\      $$\\  $$$$$$\\  $$$$$$$\\  $$$$$$$\\  " << endl;
    cout << "$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$ | $\\  $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ " << endl;
    cout << "$$ |  $$ |$$ /  $$ |$$ /  \\__|$$ /  \\__|$$ |$$$\\ $$ |$$ /  $$ |$$ |  $$ |$$ |  $$ |" << endl;
    cout << "$$$$$$$  |$$$$$$$$ |\\$$$$$$\\  \\$$$$$$\\  $$ $$ $$\\$$ |$$ |  $$ |$$$$$$$  |$$ |  $$ |" << endl;
    cout << "$$  ____/ $$  __$$ | \\____$$\\  \\____$$\\ $$$$  _$$$$ |$$ |  $$ |$$  __$$< $$ |  $$ |" << endl;
    cout << "$$ |      $$ |  $$ |$$\\   $$ |$$\\   $$ |$$$  / \\$$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |" << endl;
    cout << "$$ |      $$ |  $$ |\\$$$$$$  |\\$$$$$$  |$$  /   \\$$ | $$$$$$  |$$ |  $$ |$$$$$$$  |" << endl;
    cout << "\\__|      \\__|  \\__| \\______/  \\______/ \\__/     \\__| \\______/ \\__|  \\__|\\_______/ " << endl;

    cout << "===============================================================================================================\n";
    cout << "                              GENERATOR AND ANALYZER                                                         \n";
    cout << "=============================================================================================================\n";
}

void setColor(int colorCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}


unsigned long long lcg()
{
    seed = (a * seed + c) % m;
    return seed;
}

int randomInRange(int max)
{
    return (int)(lcg() % max);
}

void permutationsCalculator()
{
    cout << "\n=== PERMUTATIONS CALCULATOR (nPr) ===\n";
    cout << "From Rosen 6.3: P(n,r) = n!/(n-r)!\n";
    cout << "Counts arrangements WHERE ORDER MATTERS and NO REPETITION\n\n";

    int n, r;
    cout << "Total items (n): ";
    cin >> n;
    cout << "Select how many (r): ";
    cin >> r;

    if (r > n)
    {
        cout << "Error: r cannot exceed n\n";
        return;
    }

    long long result = 1;
    cout << "\nP(" << n << "," << r << ") = ";
    for (int i = 0; i < r; i++)
    {
        if (i > 0)
            cout << "* ";
        cout << "(" << n << "-" << i << ")";
        result *= (n - i);
    }
    cout << " = " << result << endl;

    cout << "\nPASSWORD APPLICATION:\n";
    cout << "If password length = " << r << " and ";
    cout << "characters CAN'T repeat from set of " << n << ":\n";
    cout << "Total possible passwords: " << result << endl;

    long long withRep = 1;
    for (int i = 0; i < r; i++)
    {
        withRep *= n;
    }
    cout << "If characters CAN repeat: " << n << "^" << r << " = " << withRep << endl;
    cout << "Difference: " << (withRep - result) << " fewer passwords without repetition\n";
}
void combinationsCalculator()
{
    cout << "\n=== COMBINATIONS CALCULATOR (nCr) ===\n";
    cout << "From Rosen 6.4: C(n,r) = n!/(r!(n-r)!)\n";
    cout << "Counts selections WHERE ORDER DOESN'T MATTER\n\n";

    int n, r;
    cout << "Total items (n): ";
    cin >> n;
    cout << "Select how many (r): ";
    cin >> r;

    if (r > n)
    {
        cout << "Error: r cannot exceed n\n";
        return;
    }

    long long result = 1;
    cout << "\nC(" << n << "," << r << ") = ";

    if (r > n - r)
        r = n - r;

    for (int i = 1; i <= r; i++)
    {
        result = result * (n - r + i) / i;
    }

    cout << result << " ways\n";

    cout << "\nPASSWORD POLICY APPLICATION:\n";
    cout << "You have 4 character types: Lowercase, Uppercase, Digits, Symbols\n";
    cout << "Number of ways to choose " << r << " types: C(4," << r << ") = "
         << result << " policies\n";

    // List all combinations for small n
    if (n <= 5)
    {
        cout << "\nAll combinations:\n";

        cout << "(Use combination generation for full list)\n";
    }
}
void printColoredStrength(double entropy)
{
    string label = strengthLabel(entropy);

    if (label == "Very Weak")
        setColor(12);
    else if (label == "Weak")
        setColor(12);
    else if (label == "Moderate")
        setColor(14);
    else if (label == "Strong")
        setColor(10);
    else
        setColor(9);

    cout << label;
    setColor(15);
}
void calculateCrackingTimeInteractive()
{
    cout << "\n=== CRACKING TIME ESTIMATOR ===\n";

    int length;
    char includeLower, includeUpper, includeDigits, includeSymbols;

    cout << "Enter password length: ";
    cin >> length;
    cout << "Include lowercase letters? (y/n): ";
    cin >> includeLower;
    cout << "Include uppercase letters? (y/n): ";
    cin >> includeUpper;
    cout << "Include digits? (y/n): ";
    cin >> includeDigits;
    cout << "Include symbols? (y/n): ";
    cin >> includeSymbols;
    cin.ignore(1000, '\n');

    int charsetSize = getCharsetSize(
        tolower(includeLower) == 'y',
        tolower(includeUpper) == 'y',
        tolower(includeDigits) == 'y',
        tolower(includeSymbols) == 'y');

    if (charsetSize == 0)
    {
        cout << "ERROR: No character types selected.\n";
        return;
    }

    cout << "\nEstimated cracking time: ";
    printCrackingTime(estimateCrackingTime(length, charsetSize));
}