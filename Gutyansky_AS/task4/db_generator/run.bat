chcp 1251
echo "Конвертация excel файла..."
pip install -r "requirements.txt"
python ./data_generator.py
echo "Конвертация завершена"
pause