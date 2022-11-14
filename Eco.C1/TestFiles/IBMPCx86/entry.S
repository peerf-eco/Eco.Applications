.code16
.text
.extern _run
.global _start
_start:
    cld
    call _run
