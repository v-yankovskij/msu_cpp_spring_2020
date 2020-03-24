import subprocess

def check(proc, expr, result):
    out = subprocess.run([proc, expr], stdout=subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print(expr, ' - error')
        print('Expected: ', result)
        print('Got:' out.stdout)
    else:
        print(expr, ' - correct')

check('./Parser', 'sator arepo tenet opera rotas', 'start string string string string string stop ')
check('./Parser', '2 + 2 = 4', 'start number string number string number stop ') 
