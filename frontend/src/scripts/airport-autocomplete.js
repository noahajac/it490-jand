const registerAirportField = (element) => {
  element.addEventListener('change', async (evt) => {
    console.log(evt.target.value);
    const results = await fetch('/api/check-airport/?search=' + encodeURIComponent(evt.target.value), {
      method: 'get',
      credentials: 'include'
    }).then((res) => { return res.json() });
    console.log(results);
  });
};
