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

test "PINA: 0x03, 0x02, 0x03; cnt: 9 => PORTC: 9, 9, 9; state: Wait, Inc, Wait"
set state = Wait
set cnt = 9
setPINA 0x03
continue 5
expectPORTC 9
expect state Wait
setPINA 0x02
continue 5
expectPORTC 9
expect state Inc
setPINA 0x03
continue 5
expectPORTC 9
expect state Wait
checkResult

test "PINA: 0x03, 0x01, 0x03; cnt: 0 => PORTC: 0, 0, 0; state: Wait, Dec, Wait"
set state = Wait
set cnt = 0
setPINA 0x03
continue 5
expectPORTC 0
expect state Wait
setPINA 0x01
continue 5
expectPORTC 0
expect state Dec
setPINA 0x03
continue 5
expectPORTC 0
expect state Wait
checkResult

test "PINA: 0x01, 0x00, 0x01; cnt: 5 => PORTC: 5, 0, 0; state: Dec, Rst, Rst"
set state = Dec
set cnt = 5
setPINA 0x01
continue 5
expectPORTC 5
expect state Dec
setPINA 0x00
continue 5
expectPORTC 0
expect state Rst
setPINA 0x01
continue 5
expectPORTC 0
expect state Rst
checkResult

test "PINA: 0x02, 0x00, 0x02; cnt: 5 => PORTC: 5, 0, 0; state: Inc, Rst, Rst"
set state = Inc
set cnt = 5
setPINA 0x02
continue 5
expectPORTC 5
expect state Inc
setPINA 0x00
continue 5
expectPORTC 0
expect state Rst
setPINA 0x02
continue 5
expectPORTC 0
expect state Rst
checkResult

test "PINA: 0x03, 0x00, 0x03; cnt: 5 => PORTC: 5, 0, 0; state: Wait, Rst, Wait"
set state = Wait
set cnt = 5
setPINA 0x03
continue 5
expectPORTC 5
expect state Wait
setPINA 0x00
continue 5
expectPORTC 0
expect state Rst
setPINA 0x03
continue 5
expectPORTC 0
expect state Wait
checkResult

test "PINA: 0x03, 0x02, 0x03, 0x01, 0x03, 0x02, 0x01, 0x02; cnt: 5 => PORTC: 5, 6, 6, 5, 5, 6, 5, 6; state: Wait, Inc, Wait, Dec, Wait, Inc, Dec, Inc"
set state = Wait
set cnt = 5
setPINA 0x03
continue 5
expectPORTC 5
expect state Wait
setPINA 0x02
continue 5
expectPORTC 6
expect state Inc
setPINA 0x03
continue 5
expectPORTC 6
expect state Wait
setPINA 0x01
continue 5
expectPORTC 5
expect state Dec
setPINA 0x03
continue 5
expectPORTC 5
expect state Wait
setPINA 0x02
continue 5
expectPORTC 6
expect state Inc
setPINA 0x01
continue 5
expectPORTC 5
expect state Dec
setPINA 0x02
continue 5
expectPORTC 6
expect state Inc
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
