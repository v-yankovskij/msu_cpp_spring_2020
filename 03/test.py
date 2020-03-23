import subprocess

def check(proc, expr, result):
    out = subprocess.run([proc, expr], stdout=subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print(expr, ' - error')
        print('Expected: ', result)
        print('Got:' out.stdout)
    else:
        print(expr, ' - correct')

check('./Matrix', '0 2 2 1 2 3 4 0 0', '1')
check('./Matrix', '1 2 2 1 2 3 4 1 2 3 4', '1')
check('./Matrix', '1 2 2 1 2 3 4 4 3 2 1', '0')
