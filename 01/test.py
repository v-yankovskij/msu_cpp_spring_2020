import subprocess

def check(proc, expr, result):
    out = subprocess.run([proc, expr], stdout=subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print(expr, ' - error')
        print('Expected: ', result)
        print('Got:' out.stdout)
    else:
        print(expr, ' - correct')
        
check('./LinearAllocator', '100 25 50 75 r 90', 'allocated allocated out of memory allocated ')
check('./LinearAllocator', '15 100 4 9 4 r 4', 'out of memory allocated allocated out of memory allocated')
