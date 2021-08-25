# Test file for "Lab5"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03 => PORTC: 33, 18, 18, 12, 12, 18, 18, 33, 33; state: Display, Wait, Display, Wait, Display, Wait, Display, Wait, Display"
set state = Display
setPINA 0x03
continue 5
expectPORTC 33
expect state Display
setPINA 0x02
continue 5
expectPORTC 18
expect state Wait
setPINA 0x03
continue 5
expectPORTC 18
expect state Display
setPINA 0x02
continue 5
expectPORTC 12
expect state Wait
setPINA 0x03
continue 5
expectPORTC 12
expect state Display
setPINA 0x02
continue 5
expectPORTC 18
expect state Wait
setPINA 0x03
continue 5
expectPORTC 18
expect state Display
setPINA 0x02
continue 5
expectPORTC 33
expect state Wait
setPINA 0x03
continue 5
expectPORTC 33
expect state Display
checkResult

test "PINA: 0x0F, 0x07, 0x0F, 0x0B, 0x0F => PORTC: 33, 33, 33, 33, 33; state: Display"
set state = Display
setPINA 0x0F
continue 5
expectPORTC 33
expect state Display
setPINA 0x07
continue 5
expectPORTC 33
expect state Display
setPINA 0x0F
continue 5
expectPORTC 33
expect state Display
setPINA 0x0B
continue 5
expectPORTC 33
expect state Display
setPINA 0x0F
continue 5
expectPORTC 33
expect state Display
checkResult

test "PINA: 0x0F, 0x0C, 0x0F, 0x0A, 0x0F, 0x06, 0x0F => PORTC: 33, 18, 18, 12, 12, 18, 18; state: Display, Wait, Diplay, Wait, Display, Wait, Display"
set state = Display
setPINA 0x0F
continue 5
expectPORTC 33
expect state Display
setPINA 0x0C
continue 5
expectPORTC 18
expect state Wait
setPINA 0x0F
continue 5
expectPORTC 18
expect state Display
setPINA 0x0A
continue 5
expectPORTC 12
expect state Wait
setPINA 0x0F
continue 5
expectPORTC 12
expect state Display
setPINA 0x06
continue 5
expectPORTC 18
expect state Wait
setPINA 0x0F
continue 5
expectPORTC 18
expect state Display
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
