OUTPUT_FORMAT(binary)
ENTRY(_start)

SECTIONS
{
    . = 0x100;

    .text :
    {
        *(.text)
        *(.rodata)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
        *(COMMON)
    }

    PROVIDE(end = .);
}
