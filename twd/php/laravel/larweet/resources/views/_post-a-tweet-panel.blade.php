<div class="border border-blue-400 rounded-2xl px-8 py-6 mb-8">
    <form method="post" action="/tweets">
        @csrf
        <textarea name="body" class="w-full focus:outline-none" placeholder="Larweet something!"></textarea>

        <hr class="my-4">

        @error('body')
            <p class="text-sm text-red-500 mt-4 mb-4">Bruh, {{ $message }}</p>
        @enderror

        <footer class="flex justify-between">
            <img src="{{ auth()->user()->getAvatar(40) }}" 
                alt="avatar"
                class="rounded-full mr-2"
            >
            <button class="bg-blue-500 rounded-2xl shadow py-2 px-2 text-white">Larweet</button>
        </footer>
    </form>
</div>