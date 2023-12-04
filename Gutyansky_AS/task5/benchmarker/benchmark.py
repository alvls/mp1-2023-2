import subprocess
import os
import shutil
import json
import random
import uuid

FILES_DIR = './test_dir'
EXE_PATH = '../../x64/Release/task5.exe'
BENCHMARK_PATHS = {
    'Реальные данные (папка с файлами проекта)': 'C:\\GitHub Repos\\LAPI_VR\\Library\\ScriptAssemblies\\*.*',
    'Windows': 'C:\\Windows\\*.*',
    'Пользователь': 'C:\\Users\\Алексей\\*.*',
}

def benchmark_once(path):
    out = {}
    p = path

    result = subprocess.run([EXE_PATH, p], stdout=subprocess.PIPE)
    output = result.stdout.decode('cp1251')
    output = output.split('\n')[:-1]
    for r in output:
        sort_name, elapsed_time = r.split(':')
        out[sort_name] = float(elapsed_time) * 1000
    
    return out

data = {}

def benchmark_files(n, step = 1):
    if os.path.isdir(FILES_DIR):
        folder = FILES_DIR
        for filename in os.listdir(folder):
            file_path = os.path.join(folder, filename)
            try:
                if os.path.isfile(file_path) or os.path.islink(file_path):
                    os.unlink(file_path)
                elif os.path.isdir(file_path):
                    shutil.rmtree(file_path)
            except Exception as e:
                print('Failed to delete %s. Reason: %s' % (file_path, e))
    else:
        os.mkdir(FILES_DIR)


    sizes = list(range(1, n+1))
    random.shuffle(sizes)
    sss = 'a'*n
    for i in range(n):
        filename = str(uuid.uuid4())
        with open(os.path.join(FILES_DIR, f'{filename}.txt'), 'w') as f:
            f.write(sss[0:sizes[i]])
        
        if step == 1 or (i % step == 0):
            data[i] = benchmark_once(os.path.join(FILES_DIR, f'*.*'))

        if i % (step*100):
            print(f'Progress: {i / (n+1) * 100}%')

    folder = FILES_DIR
    for filename in os.listdir(folder):
        file_path = os.path.join(folder, filename)
        try:
            if os.path.isfile(file_path) or os.path.islink(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)
        except Exception as e:
            print('Failed to delete %s. Reason: %s' % (file_path, e))
    os.rmdir(FILES_DIR)
    
benchmark_files(2000, 1)

for name in BENCHMARK_PATHS:
    data[name] = benchmark_once(BENCHMARK_PATHS[name])

with open("benchmark_result.json", "w") as fp:
    json.dump(data , fp)


#print(data)
    