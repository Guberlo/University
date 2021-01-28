<x-master>
    <section class="px-8">
        <main class="container mx-auto">
            
            <div class="lg:flex lg:justify-between">
                <div class="lg:w-32">
                    @include('_sidebar-links')
                </div>

            {{ $slot }}

                <div class="lg:w-1/6">
                    @include('_friends-list')
                </div>
            </div>

        </main>
    </section>
</x-master>