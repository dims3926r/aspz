## ЗАВДАННЯ ЗАГАЛЬНЕ ДЛЯ ВСІХ
## 9.1

### Умова

Напишіть програму, яка читає файл /etc/passwd за допомогою команди getent passwd, щоб дізнатись, які облікові записи визначені на вашому комп’ютері.
Програма повинна визначити, чи є серед них звичайні користувачі (ідентифікатори UID повинні бути більші за 500 або 1000, залежно від вашого дистрибутива), окрім вас.

### Рішення

Програма відкриває потік до системної команди getent passwd, яка повертає інформацію про всі облікові записи користувачів у системі. Далі вона читає кожен рядок цього потоку та розбиває його на поля, відокремлені двокрапками. З кожного рядка вона отримує ім’я користувача та його UID. Потім програма визначає ім’я поточного користувача за допомогою getlogin() або змінної середовища USER. Якщо UID користувача більший за 999 (тобто це звичайний користувач), і цей користувач не є поточним користувачем, програма виводить його ім’я та UID. Наприкінці потік закривається.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p9/p9.1/image.png)

## 9.2

### Умова

Напишіть програму, яка виконує команду cat /etc/shadow від імені адміністратора, хоча запускається від звичайного користувача.
(Ваша програма повинна робити необхідне, виходячи з того, що конфігурація системи дозволяє отримувати адміністративний доступ за допомогою відповідної команди.)

### Рішення

Ця програма намагається виконати команду sudo cat /etc/shadow, яка виводить вміст системного файлу, що містить зашифровані паролі користувачів. Звичайні користувачі не мають доступу до цього файлу, тому команда виконується через sudo, тобто від імені адміністратора. Функція system() запускає цю команду в оболонці. Якщо команда не змогла запуститися (наприклад, через помилку у виклику системи), програма виведе повідомлення про помилку. Якщо команда була запущена, але завершилась з ненульовим кодом, тобто з помилкою, програма також про це повідомить. Щоб усе це працювало без запиту пароля, система повинна бути налаштована так, щоб користувач мав дозвіл виконувати саме цю команду через sudo без введення пароля. Це задається в системному файлі /etc/sudoers, інакше при запуску програма або запросить пароль, або завершиться з помилкою доступу.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p9/p9.2/image.png)

## 9.3

### Умова

Напишіть програму, яка від імені root копіює файл, який вона перед цим створила від імені звичайного користувача. Потім вона повинна помістити копію у домашній каталог звичайного користувача.
Далі, використовуючи звичайний обліковий запис, програма намагається змінити файл і зберегти зміни. Що відбудеться?
Після цього програма намагається видалити цей файл за допомогою команди rm. Що відбудеться?

### Рішення

Ця програма спочатку створює файл /tmp/testfile.txt від імені звичайного користувача, потім за допомогою sudo копіює його у домашній каталог цього користувача під іменем copied_by_root.txt. Копіювання виконується з правами адміністратора, тому власником нового файлу стає root. Далі програма намагається відкрити цей файл для дописування (fopen з режимом "a"). Якщо у звичайного користувача немає прав на запис у файл, то ця операція завершиться помилкою. Програма повідомить про це через perror.
Після цього виконується спроба видалити файл через remove. Якщо файл належить root, але розміщується у домашньому каталозі звичайного користувача, то звичайний користувач зазвичай має право видалити його — не тому, що має доступ до самого файлу, а тому що має право змінювати вміст свого каталогу (права на каталог дозволяють це). Тому файл може бути успішно видалений, навіть якщо сам по собі недоступний для редагування.
Отже, результат буде такий: при спробі змінити файл, швидше за все, виникне помилка доступу (Permission denied), а при спробі видалення — файл буде видалено успішно.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p9/p9.3/image.png)

## 9.4

### Умова

Напишіть програму, яка по черзі виконує команди whoami та id, щоб перевірити стан облікового запису користувача, від імені якого вона запущена.
Є ймовірність, що команда id виведе список різних груп, до яких ви належите. Програма повинна це продемонструвати.

### Рішення

Ця програма спочатку виконує команду whoami, яка показує ім’я користувача, від імені якого запущено програму. Далі вона виконує команду id, яка надає детальну інформацію про користувача: його UID (ідентифікатор користувача), GID (ідентифікатор основної групи), а також список усіх груп, до яких цей користувач належить. Таким чином, програма демонструє як поточне ім’я користувача, так і його участь у різних групах системи.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p9/p9.4/image.png)

## 9.5

### Умова

Напишіть програму, яка створює тимчасовий файл від імені звичайного користувача. Потім від імені суперкористувача використовує команди chown і chmod, щоб змінити тип володіння та права доступу. Програма повинна визначити, в яких випадках вона може виконувати читання та запис файлу, використовуючи свій обліковий запис.

### Рішення

Ця програма створює тимчасовий файл у директорії /tmp від імені звичайного користувача, записує в нього текст, а потім за допомогою команд sudo chown і sudo chmod змінює власника файлу на root і встановлює права доступу 600, що означає: лише власник (тобто root) має право читання й запису. Після цього програма перевіряє, чи може звичайний користувач прочитати або редагувати файл. Через зміну власника на root і встановлення прав 600, звичайний користувач не має доступу ні до читання, ні до запису, тому обидва відкриття файлу (на читання й запис) завершаться невдачею.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p9/p9.5/image.png)

## 9.6

### Умова

Напишіть програму, яка виконує команду ls -l, щоб переглянути власника і права доступу до файлів у своєму домашньому каталозі, в /usr/bin та в /etc.
Продемонструйте, як ваша програма намагається обійти різні власники та права доступу користувачів, а також здійснює спроби читання, запису та виконання цих файлів.

### Рішення

Ця програма виконує команду ls -l для трьох каталогів: домашнього (~), системного (/usr/bin) і конфігураційного (/etc), щоб вивести власників і права доступу до файлів. Далі вона перевіряє доступ до трьох конкретних файлів: /etc/passwd (зазвичай доступний для читання всім), /usr/bin/ls (виконуваний файл, доступний для виконання), та /etc/shadow (файл із хешами паролів, доступний лише root). За допомогою функції access() програма перевіряє, чи дозволено поточному користувачу читати, записувати або виконувати ці файли. Таким чином демонструється, як система безпеки обмежує доступ до ресурсів на основі прав доступу та власників файлів.

![Example Image](https://github.com/dims3926r/aspz/blob/main/p9/p9.6/image.png)

## Завдання по ВАРІАНТАХ
## 11

### Умова

Чим відрізняється виконання id у shell та з системного виклику? Протестуйте в різних середовищах.

### Рішення

Команда id, виконана в терміналі (shell), показує інформацію про того користувача, під яким ви зараз працюєте — його ідентифікатор, основну та додаткові групи. Якщо ви відкрили термінал звичайного користувача, то id покаже ваші дані. Якщо ж ви використаєте sudo id, то побачите інформацію про root.
Коли ви запускаєте id у програмі, наприклад через system("id"), то вона покаже інформацію про того користувача, від імені якого запущена сама програма. Якщо ви запускаєте програму звичайним користувачем — отримаєте його дані. Якщо ж програма запущена через sudo, або має встановлений прапорець setuid, то результат може бути іншим — вона покаже вже root або того, на кого виставлено права.
У різних середовищах результат може змінюватися: наприклад, в crontab або при запуску через систему може бути обмежене середовище, і id покаже обмежену або іншу інформацію. Тому запуск у shell і в програмі — це не одне й те саме, хоча результат часто схожий.
