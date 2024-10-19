# Importing pyttsx3 for ?
# Importing datetime for wishme function
# Importing speech_recognition for listening to user's commands
# Importing wikipedia for wikipedia query
# Importing sys for quitting out of the program
# Importing os for joining and recognizing file paths

import pyttsx3
import datetime
import speech_recognition as sr
import wikipedia
import sys
import os

engine = pyttsx3.init('sapi5') # Need to research on this!
voices = engine.getProperty('voices')
engine.setProperty('voices',voices[0].id)

def speak(audio):

    # Speaks whatever is passed as the audio argument using say attribute

    engine.say(audio)

    # Runs and waits for the user to speak
    engine.runAndWait()

def wishme():

    # Greets the user as per the time of the day

    time = int(datetime.datetime.now().hour)

    if time >= 0 and time < 12:

        speak('GoodMorning sir! I am Jarvis, AI. ')
    
    elif time >= 12 and time < 18:

        speak('GoodAfternoon sir! I am Jarvis, AI. ')

    else:

        speak('GoodEvening sir! I am Jarvis, AI. ')
    
    speak('How may I help you?!') 

def takecommand():

    '''
    Listens to user's commands
    '''

    r = sr.Recognizer()

    with sr.Microphone() as source:

        print('Listening...')
        r.energy_threshold = 3000
        r.pause_threshold = 1
        audio = r.listen(source)

    try:
        print('Recognizing...')
        query = r.recognize_google(audio, language = 'en')
        print(f'User\'s command: {query}')
    except Exception as e:

        print('I didn\'t understand it, can you repeat once more!')
        print('Listening...')
        return 'None' # Need to research on this

    return query 

def shoutout():

    speak('Who do you want me to greet sir?')

    query = takecommand().lower()
    say = (f'Shoutout to my one and only bitch, {query}!')
    return say

if __name__ == '__main__':

    wishme()

    while True:

        query = takecommand().lower()

        if 'wikipedia' in query:

            speak('Searching Wikipedia...')
            query = query.replace('wikipedia', '')  # Need to research on this
            results = wikipedia.summary(query, sentences = 2)
            speak('According to wikipedia...')
            print(results)
            speak(results)
        
        elif 'valorant' in query:

            game_dir = 'C:\\Users\\Public\\Desktop'
            
            os.startfile(os.path.join(game_dir,'VALORANT')) # Need to research

            speak('Ok opening up valorant!')
        
        # elif '84' in query:

        #     game_dir = 'C:\\Users\\ASUS\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Steam'
                
        #     os.startfile(os.path.join(game_dir,'Farlight 84')) # Need to research

        #     speak('Ok opening up Farlight 84!')

        elif 'chrome' in query:

            game_dir = 'C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs'
            speak('Ok opening up Chrome!')
            os.startfile(os.path.join(game_dir,'Google Chrome')) # Need to research

        elif 'greet' in query:

           speak(shoutout())

        elif 'quit' in query:

            speak('Ok quitting for now sir. Feel free to comeback anytime.')
            sys.exit()