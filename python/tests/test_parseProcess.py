import unittest
from shell import parseProcesses

class ParseProcessTester(unittest.TestCase):

    # Verify Correct Number of Processes Parsed
    def test_countProcesses_1_noArgs(self):
        processes = parseProcesses("du")
        self.assertEqual(processes[0].command, "du")
        self.assertEqual(len(processes), 1)
        self.assertEqual(len(processes[0].arguments), 0)

    def test_countProcesses_1_noArgs_emptyString(self):
        processes = parseProcesses("du \"\"")
        self.assertEqual(len(processes), 1)
        self.assertEqual(len(processes[0].arguments), 0)

    def test_countProcesses_1(self):
        processes = parseProcesses("du -l")
        self.assertEqual(len(processes), 1)
        self.assertEqual(len(processes[0].arguments), 1)

    def test_countProcesses_2_withSpaces(self):
        processes = parseProcesses('du -l | ps aux')
        self.assertEqual(len(processes), 2)

    def test_countProcesses_2_withNoSpaces(self):
        processes = parseProcesses('du -l|ps aux')
        self.assertEqual(len(processes), 2)

    def test_countProcesses_2_withMixedSpaces(self):
        processes = parseProcesses('du -l| ps aux')
        self.assertEqual(len(processes), 2)
    
    def test_countProcesses_3_withSpaces(self):
        processes = parseProcesses('du -l | ps aux | grep argument')
        self.assertEqual(len(processes), 3)

    def test_countProcesses_3_withSpacesNoArgs(self):
        processes = parseProcesses('du | ps | grep')
        self.assertEqual(len(processes), 3)

    def test_countProcesses_3_withNoSpaces(self):
        processes = parseProcesses('du -l|ps aux|grep argument')
        self.assertEqual(len(processes), 3)
    
    def test_countProcesses_3_withMixedSpaces(self):
        processes = parseProcesses('du -l |ps aux |grep argument')
        self.assertEqual(len(processes), 3)

    def test_countProcesses_3_tailingSpaces(self):
        processes_1 = parseProcesses('du -l |ps aux |grep argument   ')
        self.assertEqual(len(processes_1), 3)
    
    def test_countProcesses_3_leadingSpaces(self):
        processes_1 = parseProcesses('   du -l |ps aux |grep argument')
        self.assertEqual(len(processes_1), 3)

    def test_countProcesses_3_lessThanGreaterThan(self):
        processes_1 = parseProcesses('du -l <ps aux >grep argument')
        self.assertEqual(len(processes_1), 3)

    def test_countProcesses_3_middleManySpaces(self):
        processes_1 = parseProcesses('   du -l |ps        aux |grep argument')
        self.assertEqual(len(processes_1), 3)

    def test_countProcesses_3_greaterThanLessThan(self):
        processes_1 = parseProcesses('du -l > ps aux <grep argument')
        self.assertEqual(len(processes_1), 3)

    # Verify correct commands in parsed processes
    def test_commands_1(self):
        processes = parseProcesses('du -l')
        self.assertEqual(processes[0].command, 'du')
    
    def test_commands_3(self):
        processes = parseProcesses('du -l | ps aux | grep argument')
        
        correctCommands = ['du', 'ps', 'grep']
        for process in enumerate(processes):
            self.assertEqual(process[1].command, correctCommands[process[0]], 'Command {} incorrect'.format(process[0]))

    # Verify correct arguments in parsed processes
    def test_arguments_1(self):
        processes = parseProcesses('du -l apple')
        
        correctArguments = [
            ['-l', 'apple']
        ]
        for process in enumerate(processes):
            for argument in enumerate(process[1].arguments):
                self.assertEqual(process[1].arguments[argument[0]], correctArguments[process[0]][argument[0]], 'Command {} Argument {} incorrect'.format(process[0], argument[0]))

    def test_arguments_3Process_varyNumberOfArgs(self):
        processes = parseProcesses('du -l | ps aux apple | grep argument')
        
        correctArguments = [
            ['-l'],
            ['aux', 'apple'],
            ['argument']
        ]
        for process in enumerate(processes):
            for argument in enumerate(process[1].arguments):
                self.assertEqual(process[1].arguments[argument[0]], correctArguments[process[0]][argument[0]], 'Command {} Argument {} incorrect'.format(process[0], argument[0]))

    def test_arguments_3Process_zeroArgs(self):
        processes = parseProcesses('du | ps | grep')
        
        for process in enumerate(processes):
            self.assertEqual(len(process[1].arguments), 0, 'Command {} should have zero arguments'.format(process[0]))

    # Cause Mismatched Exceptions to occur
    def test_mismatch_quotes(self):
        self.assertRaises(Exception, parseProcesses, 'du "mismatch')
    
    def test_mismatch_quotes_2(self):
        self.assertRaises(Exception, parseProcesses, 'du "mismatch | welcome')

    def test_mismatch_quotes_3(self):
        self.assertRaises(Exception, parseProcesses, 'du "mismatch | welcome" | ps welcome "bob')