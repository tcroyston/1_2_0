# Test file for "Lab2_introToAVR"


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

# Add tests below

test "PINA: 47kg, PINB: 47kg, PINC: 47kg => PORTD = 0x8D"
setPINA 0x2F
setPINB 0x2F
setPINC 0x2F
continue 2
expectPORTD 0x8D
checkResult

test"PINA: 40kg, PINB: 20kg, PINC: 124kg => PORTD = 0xBB"
setPINA 0x28
setPINB 0x14
setPINC 0x7C
continue 2
expectPORTD 0xBB
checkResult

test "PINA: 0kg, PINB: 0kg, PINC: 0kg => PORTD = 0x00"
setPINA 0
setPINB 0
setPINC 0
continue 2
expectPORTD 0x00
checkResult

test "PINA: 0kg, PINB: 0kg, PINC: 120kg => PORTD = 0x7A"
setPINA 0
setPINB 0
setPINC 0x78
continue 2
expectPORTD 0x7A
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
