const inputField = document.getElementById('destination-display');
const valueField = document.getElementById('destination');
const submitButton = document.getElementById('create-submit');

inputField.addEventListener('change', async (evt) => {
  submitButton.disabled = true;
  const results = await fetch('/api/check-airport/?search=' + encodeURIComponent(evt.target.value), {
    method: 'get',
    credentials: 'include'
  }).then((res) => { return res.json() });

  if (results.length === 0) {
    alert('No destination found by that name. Please try again.');
  } else {
    inputField.value = results[0].name;
    valueField.value = results[0].code;
    submitButton.disabled = false;
  }

});
