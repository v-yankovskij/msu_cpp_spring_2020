import subprocess

def check(proc, expr, result):
    out = subprocess.run([proc, expr], stdout=subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print(expr, ' - error')
        print('Expected: ', result)
        print('Got:' out.stdout)
    else:
        print(expr, ' - correct')
        
check('./Pool', '', '0')
