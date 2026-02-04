; Сегодня мы изучили на моих лекциях переходы
; Данная тема безусловно является важной частью NASM
; И я решил написать программу, где мы опять таки объединим все знания которые мы получили за три последнии дня
; Сегодня мы напишем на NASM простую игру угадайку

; Указывает на то что точка входа глобальная
global _start

; секция в которой хранятся данные 
section .data
    ; prompt - метка строки
    ; db - переводится как определить байты
    prompt: db "Введите число: ", 0
    prompt_len: equ $ - prompt
    
    ; buffer - метка для буфера ввода 
    ; times 256 - повторить 256 раз
    ; db 0 - определить байт со значением 0
    buffer times 256 db 0 ; буфер для ввода (256 байт)
    
    ; секретное число
    secret_number equ 42 ; Это будет загаданное число

    ; текст и его длина
    msg_max: db "Это число большое", 0xA
    len_max: equ $ - msg_max ; equ - константа

    ; текст и его длина
    msg_equal: db "Вы угадали!", 0xA
    len_equal: equ $ - msg_equal ; equ - константа

    ; текст и его длина
    msg_min: db "Это число маленькое", 0xA
    len_min: equ $ - msg_min ; equ - константа
    
    msg_invalid: db "Неверный ввод. Попробуйте снова.", 0xA
    len_invalid: equ $ - msg_invalid

; В этой секции основная логика программы
section .text

print_string:
    ; Вызываем sys_write
    mov rax, 1          ; номер системного вызова sys_write
    mov rdi, 1          ; файловый дескриптор stdout
    mov rsi, [rsp + 8]  ; адрес строки (передается первым аргументом)
    mov rdx, [rsp + 16] ; длина строки (передается вторым аргументом)
    syscall 
    ret

read_input:
    ; Вход: адрес буфера передается через стек
    ; Выход: rax - количество считанных байт
    
    mov rax, 0          ; номер системного вызова sys_read
    mov rdi, 0          ; файловый дескриптор stdin
    mov rsi, [rsp + 8]  ; адрес буфера
    mov rdx, 256        ; максимальная длина
    syscall
    ret

string_to_int:
    ; Вход: rdi - адрес строки
    ; Выход: rax - число, -1 при ошибке
    
    xor rax, rax        ; обнуляем результат
    xor rcx, rcx        ; обнуляем счетчик
    mov rsi, 10         ; основание системы счисления
    
.convert_loop:
    movzx r8, byte [rdi + rcx] ; загружаем следующий символ
    cmp r8, 0xA         ; проверяем на символ новой строки
    je .done
    cmp r8, 0           ; проверяем на конец строки
    je .done
    cmp r8, '0'         ; проверяем, что символ цифра
    jl .error
    cmp r8, '9'
    jg .error
    
    sub r8, '0'         ; преобразуем символ в цифру
    imul rax, rsi       ; умножаем текущий результат на 10
    add rax, r8         ; добавляем новую цифру
    inc rcx             ; переходим к следующему символу
    jmp .convert_loop

.done:
    ret

.error:
    mov rax, -1         ; возвращаем -1 при ошибке
    ret

; В данном месте стартует программа
; как любая уважающая себя программа, она разделена на функции, но все начинается отсюда 
_start:
    ; Метка начала игрового цикла
.game_loop:
    ; Выводим приглашение для ввода
    push prompt_len      ; второй аргумент - длина
    push prompt          ; первый аргумент - строка
    call print_string
    add rsp, 16         ; очищаем стек (2 аргумента по 8 байт)
    
    ; Чтение ввода пользователя
    push buffer          ; аргумент - адрес буфера
    call read_input
    add rsp, 8          ; очищаем стек
    
    ; Проверяем, что что-то было введено
    cmp rax, 0
    jle .game_loop
    
    ; Преобразуем введенную строку в число 
    mov rdi, buffer      ; адрес буфера с введенными данными
    call string_to_int   ; преобразовать строку в число
    
    ; Проверяем на ошибку преобразования
    cmp rax, -1         ; сравнить результат с -1 (ошибка)
    jne .check_number
    
    ; Выводим сообщение об ошибке
    push len_invalid
    push msg_invalid
    call print_string
    add rsp, 16
    jmp .game_loop      ; если ошибка - просим ввести снова

.check_number:
    ; Сравниваем с загаданным числом
    cmp rax, secret_number
    jg .too_big
    jl .too_small
    
    ; Если равно - пользователь угадал
    push len_equal
    push msg_equal
    call print_string
    add rsp, 16
    jmp .exit

.too_big:
    push len_max
    push msg_max
    call print_string
    add rsp, 16
    jmp .game_loop
    
.too_small:
    push len_min
    push msg_min
    call print_string
    add rsp, 16
    jmp .game_loop

.exit:
    ; Завершаем программу
    mov rax, 60         ; sys_exit
    xor rdi, rdi        ; код возврата 0
    syscall