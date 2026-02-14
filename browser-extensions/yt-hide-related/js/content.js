// this bit is unused but left in for future reference
(() => {
  //let lastUrl = location.href;
  //
  //function checkUrlChange() {
  //  if (location.href !== lastUrl) {
  //    lastUrl = location.href;
  //  }
  //}
  //
  //// covers replaceState and also DOM changes outside of URL changes
  //const mo = new MutationObserver(checkUrlChange);
  //mo.observe(document.documentElement, { childList: true, subtree: true });
  //
  //const _pushState = history.pushState;
  //history.pushState = function (...args) {
  //  _pushState.apply(this, args);
  //  checkUrlChange();
  //};
  //
  //window.addEventListener("popstate", checkUrlChange);
})();
