/* Callback inputs are ignored; the third fastcall slot is callee-cleaned. */
__attribute__((fastcall)) unsigned int sub_004282D0(
    unsigned int ignored_ecx, unsigned int ignored_edx,
    const void *ignored_stack_argument)
{
    (void)ignored_ecx;
    (void)ignored_edx;
    (void)ignored_stack_argument;
    return 1u;
}
