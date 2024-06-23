let classifier;
let imageModelURL = 'https://teachablemachine.withgoogle.com/models/TVVE__2C5/';

let video;
let flippedVideo;
let label = "";

let encoder = new TextEncoder('utf-8');
let isChar = false;
let isConnected = false;
let bleDevice;
let labelCharacteristic = null;

const LED_SERVICE_UUID = '19b10000-e8f2-537e-4f6c-d104768a1214';
const LABEL_CHARACTERISTIC_UUID = '19b10001-e8f2-537e-4f6c-d104768a1214';

function preload() {
    classifier = window.ml5.imageClassifier(imageModelURL + 'model.json');
}

function setup() {
    createCanvas(640, 480);
    video = createCapture(VIDEO);
    video.size(640, 480);
    video.hide();
    flippedVideo = window.ml5.flipImage(video);
    classifyVideo();
}

function draw() {
    background(0);
    image(flippedVideo, 0, 0);
    fill(255);
    textSize(16);
    textAlign(CENTER);
    text(label, width / 2, height - 4);
}

function classifyVideo() {
    flippedVideo = ml5.flipImage(video)
    classifier.classify(flippedVideo, gotResult);
    flippedVideo.remove();
}

async function gotResult(error, results) {
    if (error) {
        console.error(error);
        return;
    }
    label = results[0].label;
    if (isChar) {
        console.log(label);
        try {
            await labelCharacteristic.writeValueWithResponse(encoder.encode(label));
        } catch (err) {
            console.error(err);
        }
    }
    classifyVideo();
}

function connectBLE() {
    if (isConnected) {
        bleDevice.gatt.disconnect();
        isConnected = false;
        isChar = false;
        document.getElementById('connect-button').innerText = 'Connect';
        document.getElementById('connect-button').classList.remove('connected');
    } else {
        navigator.bluetooth.requestDevice({ 
            filters: [
                { namePrefix: 'RSWM' }
            ],
            optionalServices: [LED_SERVICE_UUID]
        })
        .then(device => {
            bleDevice = device;
            return device.gatt.connect();
        })
        .then(async (server) => {
            isConnected = true;
            document.getElementById('connect-button').innerText = 'Disconnect';
            document.getElementById('connect-button').classList.add('connected');
            let ledService = await server.getPrimaryService(LED_SERVICE_UUID);
            labelCharacteristic = await ledService.getCharacteristic(LABEL_CHARACTERISTIC_UUID);
            isChar = true;
        })
        .catch(error => {
            console.error(error);
        });
    }
}