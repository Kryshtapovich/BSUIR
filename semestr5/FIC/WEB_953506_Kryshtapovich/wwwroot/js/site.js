$(document).ready(() => {
  $(".page-link").click(function (event) {
    event.preventDefault();
    const url = this.attributes["href"].value;
    $("#list").load(url);
    $(".active").removeClass("active disabled");
    $(this).parent().addClass("active");
    history.pushState(null, null, url);
  });
});
