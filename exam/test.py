import subprocess

def check(proc, expr, result):
    out = subprocess.run([proc, expr], stdout=subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print(expr, ' - error')
        print('Expected: ', result)
        print('Got:' out.stdout)
    else:
        print(expr, ' - correct')
        
check('./Exam', 'file1.txt 2', '111')
check('./Exam', 'file2.txt 2', '31')
check('./Exam', 'file3.txt 2', '92')
