# Проект `Jarvis`

Данный проект позволяет вам использовать голосовые команды для управления вашим умным домом.

# Зависимости

* Проект был написан на *Qt 5.6.2*

# Настройка

В домашней директории в подпапке `.jarvis` находится файл `config.ini` примерно такого вида:

	[speech]
	language=ru-RU
	query=https://tts.voicetech.yandex.net/generate?text=%1&format=mp3&lang=%2&emotion=good&speaker=zahar&key=%3
	apiKey=1c1ff0ba-ea6d-4aa2-a326-7c223634a686
	attention=60

	[search]
	query=https://yandex.ru/search/xml?user=%1&key=%2&query=%3
	apiKey=03.448641548:2e5e5053b80e4a1b25f0222131f3cd34
	user=hubbatov-rustem

	[wikipedia]
	who=кто такой
	what=что такое
	query=https://ru.wikipedia.org/w/api.php?action=opensearch&search=%1&prop=info&format=xml

	[jarvis-names]
	value1=джарвис
	valueX=jarvis

	[your-names]
	name1=сэр

	[greetings]
	greeting1=доброго времени суток
	greeting2=здравствуйте

	[accepts]
	1=да

	[rejects]
	1=нет

	[successes]
	1=готово
	2=сделано
	3=выполнено

	[fails]
	1=не получилось
	2=не смог сделать
	3=извините, не смог выполнить

	[errors]
	1=повторите запрос
	2=не расслышал
	3=что-что?

	[commands]
	1=post:http://192.168.1.10/gpio14/on#включи свет
	2=post:http://192.168.1.10/gpio14/off#выключи свет
