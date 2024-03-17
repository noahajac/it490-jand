const fromInputField = document.getElementById('from-display');
const fromValueField = document.getElementById('from');
const toInputField = document.getElementById('to-display');
const toValueField = document.getElementById('to');
const submitButton = document.getElementById('search-submit');

let checking = {
  dest: false,
  origin: false
};

const buttonCheck = () => {
  if (checking.dest || checking.origin) {
    submitButton.disabled = true;
  } else {
    submitButton.disabled = false;
  }
};

const listener = async (evt, inputField, valueField, checkKey) => {
  checking[checkKey] = true;
  buttonCheck();
  const results = await fetch('/api/check-airport/?search=' + encodeURIComponent(evt.target.value), {
    method: 'get',
    credentials: 'include'
  }).then((res) => { return res.json() });

  if (results.length === 0) {
    alert('No city found by that name. Please try again.');
  } else {
    inputField.value = results[0].name;
    valueField.value = results[0].code;
    checking[checkKey] = false;
    buttonCheck();

  }
};

if (fromInputField)
  fromInputField.addEventListener('change', (evt) => { listener(evt, fromInputField, fromValueField, 'origin'); });

if (toInputField)
  toInputField.addEventListener('change', (evt) => { listener(evt, toInputField, toValueField, 'dest'); });
