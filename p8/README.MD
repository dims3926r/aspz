## ЗАВДАННЯ ЗАГАЛЬНЕ ДЛЯ ВСІХ
## 8.1

### Умова

Чи може виклик count = write(fd, buffer, nbytes); повернути в змінній count значення, відмінне від nbytes? Якщо так, то чому? Наведіть робочий приклад програми, яка демонструє вашу відповідь.

### Рішення

Так, виклик write(fd, buffer, nbytes) може повернути значення, менше ніж nbytes. Це відбувається, якщо файловий дескриптор працює в неблокуючому режимі (наприклад, встановлений прапорець O_NONBLOCK) і буфер для запису (наприклад, pipe) заповнений або має обмежений розмір. Тоді write записує стільки байтів, скільки може, і повертає фактичну кількість записаних байтів, не чекаючи вивільнення місця.
У наведеному прикладі створюється pipe і встановлюється неблокуючий режим для кінця запису. Потім програма намагається записати великий буфер (65536 байт) у pipe. Через обмежений розмір буфера pipe і неблокуючий режим write може записати менше байт, ніж розмір буфера, і поверне фактичну кількість записаних байт у змінній count.
Таким чином, повернене значення count відрізняється від nbytes через обмеження системного буфера і режим роботи write. Це нормальна поведінка, яку потрібно враховувати при роботі з неблокуючими дескрипторами.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p8/p8.1/image.png)

## 8.2

### Умова

Є файл, дескриптор якого — fd. Файл містить таку послідовність байтів: 4, 5, 2, 2, 3, 3, 7, 9, 1, 5. У програмі виконується наступна послідовність системних викликів:
lseek(fd, 3, SEEK_SET);
read(fd, &buffer, 4);
де виклик lseek переміщує покажчик на третій байт файлу. Що буде містити буфер після завершення виклику read? Наведіть робочий приклад програми, яка демонструє вашу відповідь.

### Рішення

Виклик lseek(fd, 3, SEEK_SET) переміщує позицію читання у файлі на четвертий байт (рахунок починається з нуля), тому наступний виклик read(fd, &buffer, 4) зчитає 4 байти починаючи саме з цього байта. У файлі міститься послідовність байтів 4, 5, 2, 2, 3, 3, 7, 9, 1, 5, тому після зсуву на позицію 3 будуть читатися байти 2, 3, 3, 7. Отже, після виконання read буфер міститиме саме ці значення. Наведена програма створює файл, записує у нього цю послідовність, відкриває файл для читання, виконує зсув позиції за допомогою lseek, зчитує 4 байти у буфер і виводить їх на екран. Це підтверджує, що буфер містить байти 2 3 3 7 після виконання операції читання.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p8/p8.2/image.png)

## 8.3

### Умова

Бібліотечна функція qsort призначена для сортування даних будь-якого типу. Для її роботи необхідно підготувати функцію порівняння, яка викликається з qsort кожного разу, коли потрібно порівняти два значення.
Оскільки значення можуть мати будь-який тип, у функцію порівняння передаються два вказівники типу void* на елементи, що порівнюються.
Напишіть програму, яка досліджує, які вхідні дані є найгіршими для алгоритму швидкого сортування. Спробуйте знайти кілька масивів даних, які змушують qsort працювати якнайповільніше. Автоматизуйте процес експериментування так, щоб підбір і аналіз вхідних даних виконувалися самостійно.

Придумайте і реалізуйте набір тестів для перевірки правильності функції qsort.


### Рішення

Функція qsort використовує передану функцію порівняння для сортування елементів будь-якого типу через універсальні вказівники void*. У наведеній програмі реалізовано кілька генераторів вхідних даних: випадковий масив, впорядкований за зростанням, за спаданням, масив з однаковими елементами та масив з чергуванням двох значень. Для кожного набору даних виконується сортування за допомогою qsort, а також вимірюється час виконання операції. Після сортування перевіряється правильність результату — чи є масив відсортованим у зростаючому порядку. Результати виводяться у зрозумілій формі з позначкою успішності сортування та часом виконання. Такий підхід дозволяє автоматично тестувати різні типи вхідних даних і визначати, які з них викликають найгіршу продуктивність алгоритму швидкого сортування, а також переконатися в коректності роботи функції qsort.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p8/p8.3/image.png)

## 8.4

### Умова

Виконайте наступну програму на мові програмування С:
int main() {
  int pid;
  pid = fork();
  printf("%d\n", pid);
}
Завершіть цю програму. Припускаючи, що виклик fork() був успішним, яким може бути результат виконання цієї програми?

### Рішення

При успішному виклику fork() створюється два процеси — батьківський і дочірній. У дочірньому процесі fork() повертає 0, а у батьківському — ідентифікатор (PID) дочірнього процесу, який є додатним числом. Тому результатом виконання програми будуть два рядки: один від дочірнього процесу, який виведе Дочірній процес: pid = 0, та один від батьківського, який виведе Батьківський процес: pid дочірнього = <число>, де <число> — це PID дочірнього процесу. Порядок появи цих рядків може бути будь-яким, оскільки процеси виконуються паралельно. Якщо fork() поверне від’ємне значення, це означає помилку, і програма виведе відповідне повідомлення.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p8/p8.4/image.png)

## Завдання по ВАРІАНТАХ
## 11

### Умова

Зробіть самостійну реалізацію qsort() і порівняйте її поведінку з системною на масиві об’єктів з нестабільним порівнянням.

### Рішення

У цій програмі реалізовано власну версію qsort під назвою mysort, яка використовує класичний алгоритм швидкого сортування з вибором останнього елемента як опорного. Для порівняння використано системну бібліотечну функцію qsort. Порівняння виконане на масиві структур Item, які містять ключ key та унікальний ідентифікатор id. Функція порівняння cmp робить лише нестабільне сортування за ключем key, повертаючи 0 при рівності ключів без додаткових перевірок, тому порядок елементів з однаковим ключем може змінюватися.
Власна реалізація mysort демонструє таку саму нестабільність сортування, як і системна qsort при використанні функції cmp. Це видно у зміні початкового порядку елементів з однаковим ключем — порядок id для ключів, що повторюються, не зберігається.
Для порівняння також застосовано стабільну версію порівняння cmp_stable, яка враховує id як додатковий критерій при рівності ключів, і за допомогою системної qsort показано, що порядок елементів з однаковим ключем зберігається, тобто сортування стає стабільним.
Таким чином, власна реалізація mysort функціонує аналогічно до стандартної qsort щодо нестабільності, і для стабільного сортування потрібно або змінювати функцію порівняння, або використовувати інший алгоритм сортування.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p4/p11/image.png)
