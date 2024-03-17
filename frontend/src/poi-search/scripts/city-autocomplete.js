const destInputField = document.getElementById('destination-display');
const destValueField = document.getElementById('destination');
const submitButton = document.getElementById('search-submit');

let checking = {
  dest: false,
};

const buttonCheck = () => {
  if (checking.dest) {
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

if (destInputField)
  destInputField.addEventListener('change', (evt) => { listener(evt, destInputField, destValueField, 'dest'); });
