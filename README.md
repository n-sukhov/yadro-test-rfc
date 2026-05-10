## Тестовое задание (YADRO)

### Сборка проекта

Для сборки проекта необходимо перейти в папку проекта и выполнить:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

---

Для запуска задания необходимо выполнить:

##### Автоматический режим (запуск предустановленных тестов)

Linux / macOS:

```sh
./yadro_test_rfc auto
```

Windows:


```bat
yadro_test_rfc.exe auto
```

##### Ввод параметров для генерации синуса вручную

Linux / macOS:

```sh
./yadro_test_rfc manual
```

Windows:

```bat
yadro_test_rfc.exe manual
```

---

**Анализ с визуализацией находится в блокноте analysis.ipynb.**

*Если необходима установка python-зависимостей для проверки:*
```sh
pip install -r requirements.txt
```